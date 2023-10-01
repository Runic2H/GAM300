#include "EngineInterface.hxx"
#include "../GAM300Engine/Include/application.h"
#include "../GAM300Engine/Include/ecs/ecs.cpp"
using namespace System;
using namespace System::Runtime::InteropServices;
#pragma comment (lib, "GAM300Engine.lib")


namespace ScriptAPI
{

	void EngineInterface::HelloWorld()
	{
		System::Console::WriteLine("Hello Managed World!");
		TDS::Application::HelloWorld();

	}
    /*!*************************************************************************
    * Loads the managed script dll and adds the scriptlist to all active entities
    ***************************************************************************/
	void EngineInterface::Init()
	{
        // Load Assembly
        System::Reflection::Assembly::LoadFrom("ManagedScripts.dll");

		scripts = gcnew System::Collections::Generic::SortedList<TDS::EntityID,ScriptList^>();

        HelloWorld();
        
        for (auto i : TDS::ECS::getEntities())
        {
            scripts->Add(i, gcnew ScriptList());
        }

        updateScriptTypeList();
		System::Console::WriteLine("Hello Engine Interface Init!");
	}

    /*!*************************************************************************
    * Adds scripts from the managedscript.dll to the entity via name
    ***************************************************************************/
    bool EngineInterface::AddScriptViaName(TDS::EntityID entityId, System::String^ scriptName)
    {
        if (entityId == TDS::NULLENTITY || TDS::ECS::getEntities().size() == 0)
            return false;

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
        // We have to use this as we can’t use the normal gcnew syntax to create it as 
        // scriptType is a variable that stores a type; it itself is not a type that we can pass to gcnew.
        Script^ script = safe_cast<Script^>(System::Activator::CreateInstance(scriptType));

        // Add script to SortedList
        scripts[entityId]->Add(script);

        return true;
    }

    /*!*************************************************************************
    * Calls the update function for scripts
    ***************************************************************************/
    void EngineInterface::ExecuteUpdate()
    {
        for (int i = 0; i < scripts->Count; i++)
        {
            for each (Script ^ script in scripts[i])
            {
                script->Update();
            }
        }
    }

	namespace
    {
        /* Select Many */
        ref struct Pair
        {
            System::Reflection::Assembly^ assembly;
            System::Type^                 type;
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
}