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
		This function is the update function for Properties panel
		****************************************************************************/
		void update();

		/*!*************************************************************************
		This function is the helper function for Properties panel
		****************************************************************************/
		void ImguiComponentDisplay(std::string componentName, IComponent* componentBase);

	private:
	};
}

#endif // IMGUI_PROPERTIES
