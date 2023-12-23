/*!*************************************************************************
****
\file ImguiProperties.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions used in the Level Editor Properties
		panel
****************************************************************************
***/

#ifndef IMGUI_PROPERTIES
#define IMGUI_PROPERTIES

#include "ImguiHelper.h"

namespace TDS 
{
	class Properties : public LevelEditorPanel
	{
	public:
		/*!*************************************************************************
		This function initializes the Properties panel
		****************************************************************************/
		Properties();

		/*!*************************************************************************
		This function is the init function for Properties panel
		****************************************************************************/
		void init() {}

		/*!*************************************************************************
		This function is the update function for Properties panel
		****************************************************************************/
		void update();

		/*!*************************************************************************
		This function is the helper function for Properties panel
		****************************************************************************/
		void ImguiComponentDisplay(std::string componentName, IComponent* componentBase);

		std::vector<TDS::ScriptValues>(*getScriptVariables)(EntityID entityID, std::string scriptName);

		enum class AddComponentStage
		{
			CATEGORIES = 0,
			AUDIO = 1,
			//CINEMACHINE = 2,
			//EFFECTS = 3,
			//EVENT = 4,
			//LAYOUT = 5,
			//MESH = 6,
			MISCELLANEOUS = 7,
			NAVIGATION = 8,
			//PHYSICS2D = 9,
			PHYSICS = 10,
			//PLAYABLES = 11,
			RENDERING = 12,
			SCRIPTS = 13,
			//TILEMAP = 14,
			UI = 15,
			//VIDEO = 16,
			NEWSCRIPT = 17
		};

		float addComponentWidth;
		float addComponentHeight;

		AddComponentStage currentAddComponentStage;

	private:
		ImVec2 popupPosition;
	};
}

#endif // IMGUI_PROPERTIES
