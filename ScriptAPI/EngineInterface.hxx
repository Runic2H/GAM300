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
		* Remove Scripts via name in managed script library
		***************************************************************************/
		static bool RemoveScriptViaName(TDS::EntityID entityId, std::string scriptName);
		/*!*************************************************************************
		* Updates GameObject Name
		* Call this function if User changes the name of Entities
		***************************************************************************/
		static bool UpdateGameObjectName(TDS::EntityID entityID, std::string newName);
		/*!*************************************************************************
		* Gets Game Object List
		***************************************************************************/
		static System::Collections::Generic::SortedList<TDS::EntityID, Tuple<System::String^, GameObject^>^>^ GetGameObjectList();
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
		* Calls all script FixedUpdate function
		***************************************************************************/
		static void ExecuteFixedUpdate();
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
		* Remove Entity from scriptList
		* Call this function when entity gets removed
		***************************************************************************/
		static void RemoveEntity(TDS::EntityID entityId);
		/*!*************************************************************************
		* Getting all the scripts from scriptList
		***************************************************************************/
		static std::vector<std::string> GetAllScripts();

		/*!*************************************************************************
		* Getting script isEnabled
		***************************************************************************/
		static bool IsScriptEnabled(TDS::EntityID entityId, std::string script);

		// Updated functions to handle all variable types
		//static TDS::ScriptValues GetVariable(TDS::EntityID entityId, std::string script, std::string variableName);
		/*!*************************************************************************
		* Getting variables in the script (that is either SerializedField or 
		public)
		***************************************************************************/
		static std::vector<TDS::ScriptValues> GetVariables(TDS::EntityID entityId, std::string script);
		/*!*************************************************************************
		* Getting variables in the script (that is either SerializedField or 
		public, but not in HideInInspector)
		***************************************************************************/
		static std::vector<TDS::ScriptValues> GetVariablesEditor(TDS::EntityID entityId, std::string script);
		/*!*************************************************************************
		* Setting a variable in the script
		***************************************************************************/
		static void SetVariable(TDS::EntityID entityId, std::string script, TDS::ScriptValues variableInfo);
		/*!*************************************************************************
		* Setting all variables in the script (that was serialized)
		***************************************************************************/
		static void SetVariables(TDS::EntityID entityId, std::string script, std::vector<TDS::ScriptValues>& allVariableInfo);

		/*!*************************************************************************
		* Getting the entity's gameObject (used in Serialization class)
		***************************************************************************/
		static GameObject^ GetGameObject(TDS::EntityID entityId);
		/*!*************************************************************************
		* Getting the script reference of the entity (used in Serialization class)
		***************************************************************************/
		static Script^ GetScriptReference(TDS::EntityID entityId, System::String^ script);

		/*!*************************************************************************
		* Calls all script OnTriggerEnter function
		***************************************************************************/
		static void ExecuteOnTriggerEnter(TDS::EntityID trigger, TDS::EntityID collider);
		/*!*************************************************************************
		* Calls all script OnTriggerEnter function
		***************************************************************************/
		static void ExecuteOnTriggerStay(TDS::EntityID trigger, TDS::EntityID collider);
		/*!*************************************************************************
		* Calls all script OnTriggerEnter function
		***************************************************************************/
		static void ExecuteOnTriggerExit(TDS::EntityID trigger, TDS::EntityID collider);

		using ScriptList = System::Collections::Generic::Dictionary<String^, Script^>;
		using NameScriptPair = System::Collections::Generic::KeyValuePair<String^, Script^>;
		static System::Collections::Generic::SortedList<TDS::EntityID, ScriptList^>^ GetScriptList();

	private:
		//(^)* reference to managed pointer
		static System::Collections::Generic::SortedList<TDS::EntityID, Tuple<System::String^, GameObject^>^>^ gameObjectList;
		static System::Collections::Generic::SortedList<TDS::EntityID, ScriptList^>^ scripts;
		static System::Collections::Generic::IEnumerable<System::Type^>^ scriptTypeList;
		/*!*************************************************************************
		* Updates script Type list
		***************************************************************************/
		static void updateScriptTypeList();
		static System::Runtime::Loader::AssemblyLoadContext^ loadContext;

		static float fixedUpdateTimer{0.0f};
		static float mAccumulatedTime{0.0f};
	};
}