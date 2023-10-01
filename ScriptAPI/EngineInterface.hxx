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
#include "ecs/ecs.h"

namespace ScriptAPI
{
	public ref class EngineInterface
	{
	public:
		static void HelloWorld();
		/*!*************************************************************************
		* Initializes the scriptlist for all active entities
		***************************************************************************/
		static void Init();
		/*!*************************************************************************
		* Add Scripts via name in managed script library
		***************************************************************************/
		static bool AddScriptViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Calls all script updates function
		***************************************************************************/
		static void ExecuteUpdate();

	private:
		//(^)* reference to managed pointer
		using ScriptList = System::Collections::Generic::List<Script^>;
		static System::Collections::Generic::SortedList<TDS::EntityID,ScriptList^>^ scripts;
		static System::Collections::Generic::IEnumerable<System::Type^>^ scriptTypeList;
		/*!*************************************************************************
		* Updates script Type list
		***************************************************************************/
		static void updateScriptTypeList();
	};
}