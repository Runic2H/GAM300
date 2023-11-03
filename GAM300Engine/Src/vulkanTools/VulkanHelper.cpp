#include "vulkanTools/VulkanHelper.h"

VkShaderStageFlagBits TDS::ShaderFlagsToVkStage(SHADER_FLAG flag)
{
	switch (flag)
	{
	case SHADER_FLAG::VERTEX:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
	case SHADER_FLAG::FRAGMENT:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
	case SHADER_FLAG::COMPUTE_SHADER:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;
	default:
		return VkShaderStageFlagBits::VK_SHADER_STAGE_ALL;
	}
}