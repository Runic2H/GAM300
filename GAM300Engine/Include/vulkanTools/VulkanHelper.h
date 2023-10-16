#pragma once
#include "Shader/ShaderData.h"
#include "Logger/Logger.h"
#include <vulkan/vulkan.h>
namespace TDS
{
#define VK_ASSERT(result, msg)\
	{\
		if (result != VK_SUCCESS)\
		{\
			TDS_ERROR(msg);\
			__debugbreak();\
		}\
	}
	VkShaderStageFlagBits ShaderFlagsToVkStage(SHADER_FLAG flag);

}