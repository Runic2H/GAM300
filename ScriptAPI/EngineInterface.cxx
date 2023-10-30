#include "EngineInterface.hxx"
#include "Debug.hxx"
#include "TypeConversion.hxx"
#include "HelperFunctions.hxx"
using namespace System;
using namespace System::Runtime::InteropServices;
#pragma comment (lib, "GAM300Engine.lib")

namespace ScriptAPI
{
    /*!*************************************************************************
    * Loads the managed script dll and adds the scriptlist to all active entities
    ***************************************************************************/
    void EngineInterface::Init()
    {
        using namespace System::IO;
        loadContext = gcnew System::Runtime::Loader::AssemblyLoadContext(nullptr, true);

        // Load assembly
        FileStream^ managedLibFile = File::Open
        (
            "ManagedScripts.dll",
            FileMode::Open, FileAccess::Read, FileShare::Read
        );
        loadContext->LoadFromStream(managedLibFile);
        managedLibFile->Close();

        // Load Assembly
        /*System::Reflection::Assembly::LoadFrom("ManagedScripts.dll");*/

        scripts = gcnew System::Collections::Generic::SortedList<TDS::EntityID, ScriptList^>();
        gameObjectList = gcnew System::Collections::Generic::SortedList<TDS::EntityID, Tuple<System::String^, GameObject^>^>();

        //for (auto i : TDS::ecs.getEntities())
        //{
        //    scripts->Add(i, gcnew ScriptList());
        //}

        updateScriptTypeList();
        System::Console::WriteLine("Hello Engine Interface Init!");
    }

    void EngineInterface::AddScriptList(TDS::EntityID entityID) // New entity
    {
        if (!scripts->ContainsKey(entityID))
        {
            scripts->Add(entityID, gcnew ScriptList());
            gameObjectList->Add(entityID, gcnew Tuple<String^, GameObject^>("", gcnew GameObject()));
            gameObjectList[entityID]->Item2->SetEntityID(entityID);
        }
    }

    /*!*************************************************************************
    * Adds scripts from the managedscript.dll to the entity via name
    ***************************************************************************/
    bool EngineInterface::AddScriptViaName(TDS::EntityID entityId, std::string script)
    {
        SAFE_NATIVE_CALL_BEGIN
            if (entityId == TDS::NULLENTITY)
                return false;

        String^ scriptName = toSystemString(script);

        // Remove any whitespaces
        scriptName = scriptName->Trim();

        // Look for the correct script
        System::Type^ scriptType = nullptr;
        for each (System::Type ^ type in scriptTypeList)
        {
            if (type->FullName == scriptName || type->Name == scriptName)
            {
                scriptType = type;
                break;
            }
        }

        // Failed to get any script
        if (scriptType == nullptr)
        {
            return false;
        }

        // Create the script
        // Default construct an object of the specified type. 
        // We have to use this as we can�t use the normal gcnew syntax to create it as 
        // scriptType is a variable that stores a type; it itself is not a type that we can pass to gcnew.
        Script^ script = safe_cast<Script^>(System::Activator::CreateInstance(scriptType));
        script->SetFlags();
        script->gameObject = gameObjectList[entityId]->Item2;

        // Add script to SortedList
        scripts[entityId]->Add(script->GetType()->FullName, script);

        //currentObject = script;
        //Type^ type = script->GetType();
        //currentFieldArray = type->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        return true;
        SAFE_NATIVE_CALL_END

            return false;
    }
    /*!*************************************************************************
    * Add GameObject to List
    ***************************************************************************/
    //bool EngineInterface::AddGameObjectViaName(TDS::EntityID entityId, System::String^ entityName)
    //{
    //    SAFE_NATIVE_CALL_BEGIN
    //        if (entityId == TDS::NULLENTITY)
    //            return false;

    //    entityName = entityName->Trim();

    //    gameObjectList->Add(entityName, entityId);

    //    return true;
    //        SAFE_NATIVE_CALL_END
    //        return false;
    //}
    /*!*************************************************************************
    * Updates GameObject Name
    ***************************************************************************/
    bool EngineInterface::UpdateGameObjectName(TDS::EntityID entityID, std::string newName)
    {
        SAFE_NATIVE_CALL_BEGIN
            if (gameObjectList->ContainsKey(entityID))
            {
                GameObject^ thisGameObject = gameObjectList[entityID]->Item2;
                gameObjectList[entityID] = gcnew Tuple<String^, GameObject^>(toSystemString(newName), thisGameObject);
                return true;
            }
        return false;
        SAFE_NATIVE_CALL_END
            return false;
    }

    System::Collections::Generic::SortedList<TDS::EntityID, Tuple<System::String^, GameObject^>^>^ EngineInterface::GetGameObjectList()
    {
        return gameObjectList;
    }

    /*!*************************************************************************
    * Calls all script Awake function
    ***************************************************************************/
    void EngineInterface::ExecuteAwake()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (scripts->ContainsKey(i) && TDS::ecs.getEnabledEntity(i))
            {
                for each (NameScriptPair ^ script in scripts[i])
                {
                    SAFE_NATIVE_CALL_BEGIN
                        if (!script->Value->getAwakeFlag())
                        {
                            script->Value->Awake();
                            script->Value->setAwakeFlag();
                        }
                    SAFE_NATIVE_CALL_END
                }
            }
        }
    }
    /*!*************************************************************************
    * Calls all script OnEnable function
    ***************************************************************************/
    void EngineInterface::ExecuteOnEnable()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (scripts->ContainsKey(i) && TDS::ecs.getEnabledEntity(i))
            {
                for each (NameScriptPair ^ script in scripts[i])
                {
                    SAFE_NATIVE_CALL_BEGIN
                        script->Value->OnEnable();
                    SAFE_NATIVE_CALL_END
                }
            }
        }
    }

    bool EngineInterface::ToggleScriptViaName(TDS::EntityID entityId, System::String^ scriptName)
    {
        SAFE_NATIVE_CALL_BEGIN
            if (entityId == TDS::NULLENTITY)
                return false;

        // Remove any whitespaces
        scriptName = scriptName->Trim();

        //// Look for the correct script
        //System::Type^ scriptType = nullptr;
        //for each (System::Type ^ type in scriptTypeList)
        //{
        //    if (type->FullName == scriptName || type->Name == scriptName)
        //    {
        //        scriptType = type;
        //        break;
        //    }
        //}

        //// Failed to get any script
        //if (scriptType == nullptr)
        //{
        //    return false;
        //}

        for each (NameScriptPair ^ script in scripts[entityId])
        {
            if (script->Key == scriptName)
            {
                script->Value->ToggleScript();
            }
        }
        return true;
        SAFE_NATIVE_CALL_END

            return false;
    }

    /*!*************************************************************************
    * Calls all script start function
    ***************************************************************************/
    void EngineInterface::ExecuteStart()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (scripts->ContainsKey(i) && TDS::ecs.getEnabledEntity(i))
            {
                for each (NameScriptPair ^ script in scripts[i])
                {
                    SAFE_NATIVE_CALL_BEGIN
                        if (!script->Value->getStartFlag() && script->Value->isScriptEnabled())
                        {
                            script->Value->Start();
                            script->Value->setStartFlag();
                        }
                    SAFE_NATIVE_CALL_END
                }
            }
        }
    }

    /*!*************************************************************************
    * Calls the update function for scripts
    ***************************************************************************/
    void EngineInterface::ExecuteUpdate()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (scripts->ContainsKey(i) && TDS::ecs.getEnabledEntity(i))
            {
                for each (NameScriptPair ^ script in scripts[i])
                {
                    SAFE_NATIVE_CALL_BEGIN
                        if (script->Value->isScriptEnabled())
                        {
                            script->Value->Update();
                        }
                    SAFE_NATIVE_CALL_END
                }
            }
        }
    }

    /*!*************************************************************************
    * Calls the late update function for scripts
    ***************************************************************************/
    void EngineInterface::ExecuteLateUpdate()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (scripts->ContainsKey(i) && TDS::ecs.getEnabledEntity(i))
            {
                for each (NameScriptPair ^ script in scripts[i])
                {
                    SAFE_NATIVE_CALL_BEGIN
                        if (script->Value->isScriptEnabled())
                        {
                            script->Value->LateUpdate();
                        }
                    SAFE_NATIVE_CALL_END
                }
            }
        }
    }

    /*!*************************************************************************
    * Calls the OnDisable function for scripts
    ***************************************************************************/
    void EngineInterface::ExecuteOnDisable()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (!scripts->ContainsKey(i))
            {
                continue;
            }
            for each (NameScriptPair ^ script in scripts[i])
            {
                SAFE_NATIVE_CALL_BEGIN
                    script->Value->OnDisable();
                SAFE_NATIVE_CALL_END
            }
        }
    }

    /*!*************************************************************************
    * Calls all script OnDestroy function
    ***************************************************************************/
    void EngineInterface::ExecuteOnDestroy()
    {
        for each (auto i in TDS::ecs.getEntities())
        {
            if (!scripts->ContainsKey(i))
            {
                continue;
            }
            for each (NameScriptPair ^ script in scripts[i])
            {
                SAFE_NATIVE_CALL_BEGIN
                    script->Value->OnDestroy();
                SAFE_NATIVE_CALL_END
            }
        }
    }
    /*!*************************************************************************
    * Reloads the script assembly
    ***************************************************************************/
    void EngineInterface::Reload()
    {
        // Clear all references to types in the script assembly we are going to unload
        scripts->Clear();
        gameObjectList->Clear();
        scriptTypeList = nullptr;
        // Unload
        loadContext->Unload();
        loadContext = nullptr;
        // Wait for unloading to finish
        System::GC::Collect();
        System::GC::WaitForPendingFinalizers();
        // Load the assembly again
        Init();
    }

    bool EngineInterface::HasScriptViaName(TDS::EntityID entityId, std::string script)
    {
        SAFE_NATIVE_CALL_BEGIN
        if (entityId == TDS::NULLENTITY)
            return false;

        System::String^ scriptName = toSystemString(script);

        // Remove any whitespaces
        scriptName = scriptName->Trim();

        // Look for the correct script
        System::Type^ scriptType = nullptr;
        for each (NameScriptPair ^ script in scripts[entityId])
        {
            if (script->Key == scriptName)
            {
                return true;
            }
        }

        // Failed to get any script
        return false;

        SAFE_NATIVE_CALL_END
    }

    std::vector<std::string> EngineInterface::GetAllScripts()
    {
        std::vector<std::string> allScripts;

        for each (System::Type ^ type in scriptTypeList)
        {
            allScripts.emplace_back(toStdString(type->FullName));
        }

        return allScripts;
    }

    std::vector<TDS::ScriptValues> EngineInterface::GetScriptVariables(TDS::EntityID entityId, std::string script)
    {
        std::vector<TDS::ScriptValues> scriptValues;

        if (entityId == TDS::NULLENTITY)
        {
            return scriptValues;
        }

        // Remove any whitespaces
        auto scriptName = toSystemString(script);

        scriptName = scriptName->Trim();

        Object^ obj = scripts[entityId][scriptName];

        // Failed to get any script
        if (obj == nullptr)
        {
            return scriptValues;
        }

        Type^ type = obj->GetType();
        array<FieldInfo^>^ fields = type->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        for each (FieldInfo ^ field in fields) 
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0)
            {
                //System::Console::WriteLine(field->Name);
                //System::Console::WriteLine(field->FieldType);
                //System::Console::WriteLine(field->GetValue(obj));

                TDS::ScriptValues newScriptValue;

                newScriptValue.name = toStdString(field->Name);
                newScriptValue.type = toStdString(field->FieldType->ToString());

                if (field->GetValue(obj) != nullptr)
                {
                    if (field->FieldType->ToString() == "ScriptAPI.GameObject")
                    {
                        newScriptValue.referenceEntityID = safe_cast<GameObject^>(field->GetValue(obj))->GetEntityID();
                    }
                    else if (field->FieldType->ToString() == "System.Boolean"
                        || field->FieldType->ToString() == "System.Int16"
                        || field->FieldType->ToString() == "System.Int32"
                        || field->FieldType->ToString() == "System.Int64"
                        || field->FieldType->ToString() == "System.UInt16"
                        || field->FieldType->ToString() == "System.UInt32"
                        || field->FieldType->ToString() == "System.UInt64"
                        || field->FieldType->ToString() == "System.Byte"
                        || field->FieldType->ToString() == "System.SByte"
                        || field->FieldType->ToString() == "System.Double"
                        || field->FieldType->ToString() == "System.Single"
                        || field->FieldType->ToString() == "System.Char"
                        || field->FieldType->ToString() == "System.String")
                    {
                        newScriptValue.value = toStdString(field->GetValue(obj)->ToString());
                    }
                    else // Script
                    {
                        newScriptValue.referenceEntityID = safe_cast<Script^>(field->GetValue(obj))->gameObject->GetEntityID();
                    }
                }

                scriptValues.emplace_back(newScriptValue);
            }
        }

        return scriptValues;
    }

    void EngineInterface::SetValueBool(TDS::EntityID entityId, std::string script, std::string variableName, bool value)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, value);
                return;
            }
        }
    }

    void EngineInterface::SetValueInt(TDS::EntityID entityId, std::string script, std::string variableName, int value)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, value);
                return;
            }
        }
    }

    void EngineInterface::SetValueDouble(TDS::EntityID entityId, std::string script, std::string variableName, double value)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, value);
                return;
            }
        }
    }

    void EngineInterface::SetValueFloat(TDS::EntityID entityId, std::string script, std::string variableName, float value)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, value);
                return;
            }
        }
    }

    void EngineInterface::SetValueString(TDS::EntityID entityId, std::string script, std::string variableName, std::string value)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, toSystemString(value));
                return;
            }
        }
    }

    //void EngineInterface::SetValueChar(TDS::EntityID entityId, std::string script, std::string variableName, char value)
    //{
    //    String^ variable = toSystemString(variableName);

    //    Object^ currentObject = scripts[entityId][toSystemString(script)];

    //    if (currentObject == nullptr)
    //    {
    //        return;
    //    }

    //    array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

    //    if (currentFieldArray == nullptr)
    //    {
    //        return;
    //    }

    //    for each (FieldInfo^ field in currentFieldArray)
    //    {
    //        if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
    //        {
    //            if (value == '\0')
    //            {
    //                value = 'a';
    //            }
    //            System::Console::WriteLine(value);
    //            field->SetValue(currentObject, value);
    //            System::Console::WriteLine(value);
    //            return;
    //        }
    //    }
    //}

    void EngineInterface::SetGameObject(TDS::EntityID entityId, std::string script, std::string variableName, TDS::EntityID gameObjectEntityID)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, gameObjectList[gameObjectEntityID]->Item2);
                return;
            }
        }
    }

    void EngineInterface::SetScript(TDS::EntityID entityId, std::string script, std::string variableName, TDS::EntityID gameObjectEntityID, std::string scriptReference)
    {
        String^ variable = toSystemString(variableName);

        Object^ currentObject = scripts[entityId][toSystemString(script)];

        if (currentObject == nullptr)
        {
            return;
        }

        array<FieldInfo^>^ currentFieldArray = currentObject->GetType()->GetFields(BindingFlags::Public | BindingFlags::Instance | BindingFlags::NonPublic);

        if (currentFieldArray == nullptr)
        {
            return;
        }

        for each (FieldInfo^ field in currentFieldArray)
        {
            if (field->GetCustomAttributes(SerializeFieldAttribute::typeid, true)->Length > 0 && field->Name == variable)
            {
                field->SetValue(currentObject, scripts[gameObjectEntityID][toSystemString(scriptReference)]);
                System::Console::WriteLine(field->GetValue(currentObject));
                return;
            }
        }
    }

    void EngineInterface::RemoveEntity(TDS::EntityID entityId)
    {
        SAFE_NATIVE_CALL_BEGIN
            if (scripts->ContainsKey(entityId))
            {
                scripts->Remove(entityId);
                gameObjectList->RemoveAt(gameObjectList->IndexOfKey(entityId));
            }
        SAFE_NATIVE_CALL_END

        return;
    }

    namespace
    {
        /* Select Many */
        ref struct Pair
        {
            System::Reflection::Assembly^ assembly;
            System::Type^ type;
        };
        System::Collections::Generic::IEnumerable<System::Type^>^ selectorFunc(System::Reflection::Assembly^ assembly)
        {
            return assembly->GetExportedTypes();
        }
        Pair^ resultSelectorFunc(System::Reflection::Assembly^ assembly, System::Type^ type)
        {
            Pair^ p = gcnew Pair();
            p->assembly = assembly;
            p->type = type;
            return p;
        }
        /* Where */
        bool predicateFunc(Pair^ pair)
        {
            return pair->type->IsSubclassOf(Script::typeid) && !pair->type->IsAbstract;
        }
        /* Select */
        System::Type^ selectorFunc(Pair^ pair)
        {
            return pair->type;
        }
    }

    /*!*************************************************************************
    * Updates script type list
    ***************************************************************************/
    void EngineInterface::updateScriptTypeList()
    {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Linq;
        using namespace System::Collections::Generic;
        /* Select Many: Types in Loaded Assemblies */
        IEnumerable<Assembly^>^ assemblies = AppDomain::CurrentDomain->GetAssemblies();
        Func<Assembly^, IEnumerable<Type^>^>^ collectionSelector = gcnew Func<Assembly^, IEnumerable<Type^>^>(selectorFunc);
        Func<Assembly^, Type^, Pair^>^ resultSelector = gcnew Func<Assembly^, Type^, Pair^>(resultSelectorFunc);
        IEnumerable<Pair^>^ selectManyResult = Enumerable::SelectMany(assemblies, collectionSelector, resultSelector);
        /* Where: Are concrete Scripts */
        Func<Pair^, bool>^ predicate = gcnew Func<Pair^, bool>(predicateFunc);
        IEnumerable<Pair^>^ whereResult = Enumerable::Where(selectManyResult, predicate);
        /* Select: Select them all */
        Func<Pair^, Type^>^ selector = gcnew Func<Pair^, Type^>(selectorFunc);
        scriptTypeList = Enumerable::Select(whereResult, selector);
    }

    System::Collections::Generic::SortedList<TDS::EntityID, EngineInterface::ScriptList^>^ EngineInterface::GetScriptList()
    {
        return scripts;
    }

    // To do
    GameObject^ FindGameObjectViaName(String^ name)
    {
        //System::Console::WriteLine("called in engine interfacee");
        for each (auto entityNameID in EngineInterface::GetGameObjectList())
        {
            if (entityNameID.Value->Item1 == name)
            {
                return entityNameID.Value->Item2;
            }
        }

        return nullptr;
    }
}