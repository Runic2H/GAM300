//set up temporary for now till we get the engine out and export our functions 
// then will transfer to gam300editor side

#ifndef TDS_IMGUI_FUNCTION_HELPER
#define TDS_IMGUI_FUNCTION_HELPER

#include <imgui/imgui.h>
#include "TDSMath.h"

namespace TDS 
{		
	// Helper functions
	std::string ImguiTextInput(std::string variableName, std::string textVariable);
	bool ImguiBoolInput(std::string variableName, bool boolVariable);
	int ImguiIntInput(std::string variableName, int intVariable, float speed = 1.f, int min = 0, int max = 0);
	float ImguiFloatInput(std::string variableName, float floatVariable, float speed = 1.f, float min = 0, float max = 0);
	Vec2 ImguiVec2Input(std::string variableName, Vec2 Vec2Variable);
	Vec3 ImguiVec3Input(std::string variableName, Vec3 Vec3Variable);
}

#endif // !TDS_IMGUI_FUNCTION_HELPER
