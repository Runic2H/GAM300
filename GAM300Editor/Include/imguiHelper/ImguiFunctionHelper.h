/*!*************************************************************************
****
\file ImguiFunctionHelper.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions used in the Level Editor to 
		draw our different data types
****************************************************************************
***/

#ifndef TDS_IMGUI_FUNCTION_HELPER
#define TDS_IMGUI_FUNCTION_HELPER

#include <imgui/imgui.h>
#include "TDSMath.h"

namespace TDS 
{
	/*!*************************************************************************
	This function is a helper function for draw TEXT variables
	****************************************************************************/
	std::string ImguiTextInput(std::string variableName, std::string textVariable);
	/*!*************************************************************************
	This function is a helper function for draw BOOl variables
	****************************************************************************/
	bool ImguiBoolInput(std::string variableName, bool boolVariable);
	/*!*************************************************************************
	This function is a helper function for draw INT variables
	****************************************************************************/
	int ImguiIntInput(std::string variableName, int intVariable, float speed = 1.f, int min = 0, int max = 0);
	/*!*************************************************************************
	This function is a helper function for draw FLOAT variables
	****************************************************************************/
	float ImguiFloatInput(std::string variableName, float floatVariable, float speed = 1.f, float min = 0, float max = 0);
	/*!*************************************************************************
	This function is a helper function for draw VEC2 variables
	****************************************************************************/
	Vec2 ImguiVec2Input(std::string variableName, Vec2 Vec2Variable);
	/*!*************************************************************************
	This function is a helper function for draw VEC3 variables
	****************************************************************************/
	Vec3 ImguiVec3Input(std::string variableName, Vec3 Vec3Variable);
}

#endif // !TDS_IMGUI_FUNCTION_HELPER
