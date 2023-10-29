/*!*****************************************************************************
 * \file          EngineInterface.hxx
 * \author        Elton Teo Zhe Wei
 * \par DP email: e.teo@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Entry point for C++/CLI interface for scripting language
 *******************************************************************************/
#pragma once

#include "Script.hxx"

namespace ScriptAPI
{
	public ref class EngineInterface
	{
	public:
		/*!*************************************************************************
		* Initializes the scriptlist for all active entities
		***************************************************************************/
		static void Init();

		static void AddScriptList(TDS::EntityID entityID);
		/*!*************************************************************************
		* Add Scripts via name in managed script library
		***************************************************************************/
		static bool AddScriptViaName(TDS::EntityID entityId, std::string scriptName);
		/*!*************************************************************************
		* Add GameObject to List
		* Add this function to new Entities being Created
		***************************************************************************/
		static bool AddGameObjectViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Updates GameObject Name
		* Call this function if User changes the name of Entities
		***************************************************************************/
		static bool UpdateGameObjectName(System::String^ oldName, System::String^ newName);
		/*!*************************************************************************
		* Gets Game Object List
		***************************************************************************/
		static System::Collections::Generic::SortedList<System::String^, TDS::EntityID>^ GetGameObjectList();
		/*!*************************************************************************
		* Calls all script awake function
		***************************************************************************/
		static void ExecuteAwake();
		/*!*************************************************************************
		* Calls all script OnEnable function
		***************************************************************************/
		static void ExecuteOnEnable();
		/*!*************************************************************************
		* Toggles active status on script
		***************************************************************************/
		static bool ToggleScriptViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Calls all script start function
		***************************************************************************/
		static void ExecuteStart();
		/*!*************************************************************************
		* Calls all script updates function
		***************************************************************************/
		static void ExecuteUpdate();
		/*!*************************************************************************
		* Calls all script LateUpdate function
		***************************************************************************/
		static void ExecuteLateUpdate();
		/*!*************************************************************************
		* Calls all script OnDisable function
		***************************************************************************/
		static void ExecuteOnDisable();
		/*!*************************************************************************
		* Calls all script OnDestroy function
		***************************************************************************/
		static void ExecuteOnDestroy();
		/*!*************************************************************************
		* Reloads the script assembly
		***************************************************************************/
		static void Reload();
		/*!*************************************************************************
		* Checks if Entity has Script
		***************************************************************************/
		static bool HasScriptViaName(TDS::EntityID entityId, std::string script);
		/*!*************************************************************************
		* Getting script fields for serializing
		***************************************************************************/
		static std::vector<TDS::ScriptValues> GetScriptVariables(TDS::EntityID entityID, std::string scriptName);
		/*!*************************************************************************
		* Remove Entity from scriptList
		* Call this function when entity gets removed
		***************************************************************************/
		static void RemoveEntity(TDS::EntityID entityId);
		/*!*************************************************************************
		* Getting all the scripts from scriptList
		***************************************************************************/
		static std::vector<std::string> GetAllScripts();

		static void SetValueBool(TDS::EntityID entityId, std::string script, std::string variableName, bool value);
		static void SetValueInt(TDS::EntityID entityId, std::string script, std::string variableName, int value);
		static void SetValueDouble(TDS::EntityID entityId, std::string script, std::string variableName, double value);
		static void SetValueFloat(TDS::EntityID entityId, std::string script, std::string variableName, float value);
		
		using ScriptList = System::Collections::Generic::Dictionary<String^, Script^>;
		using NameScriptPair = System::Collections::Generic::KeyValuePair<String^, Script^>;
		static System::Collections::Generic::SortedList<TDS::EntityID, ScriptList^>^ GetScriptList();

	private:
		//(^)* reference to managed pointer
		static System::Collections::Generic::SortedList<System::String^, TDS::EntityID>^ gameObjectList;
		static System::Collections::Generic::SortedList<TDS::EntityID, ScriptList^>^ scripts;
		static System::Collections::Generic::IEnumerable<System::Type^>^ scriptTypeList;
		/*!*************************************************************************
		* Updates script Type list
		***************************************************************************/
		static void updateScriptTypeList();
		static System::Runtime::Loader::AssemblyLoadContext^ loadContext;

		//static array<FieldInfo^>^ currentFieldArray;
		//static Object^ currentObject;
	};
}