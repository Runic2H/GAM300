//set up temporary for now till we get the engine out and export our functions 
// then will transfer to gam300editor side

#ifndef TDS_IMGUI_FUNCTION_HELPER
#define TDS_IMGUI_FUNCTION_HELPER

#include <imgui/imgui.h>
#include "TDSMath.h"

namespace TDS 
{		
	// Helper functions
	void ImguiTextInput(std::string variableName, std::string& textVariable);
	void ImguiBoolInput(std::string variableName, bool& boolVariable);
	void ImguiIntInput(std::string variableName, int& intVariable, float speed = 1.f, float min = 0.f, float max = 0.f);
	void ImguiFloatInput(std::string variableName, float& floatVariable, float speed = 1.f, float min = 0.f, float max = 0.f);
	void ImguiVec2Input(std::string variableName, Vec2& Vec2Variable);
	void ImguiVec3Input(std::string variableName, Vec3& Vec3Variable);
}

#endif // !TDS_IMGUI_FUNCTION_HELPER
