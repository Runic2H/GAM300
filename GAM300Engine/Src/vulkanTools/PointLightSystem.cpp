/*!*************************************************************************
****
\file PointLightSystem.cpp
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the PointLightSystem Class
****************************************************************************
***/
#include "vulkanTools/PointLightSystem.h"

namespace TDS {
	struct PointLightPushConstants {
		Vec4	m_Position{};
		Vec4	m_Color{};
		//float	m_radius;
	};

	PointLightSystem::PointLightSystem(VulkanInstance& Instance, VkRenderPass renderpass, VkDescriptorSetLayout globalsetlayout) : m_Instance(Instance) {
		createPipelineLayout(globalsetlayout);
		createPipeline(renderpass);
	}

	PointLightSystem::~PointLightSystem() {
		vkDestroyPipelineLayout(m_Instance.getVkLogicalDevice(), m_pipelineLayout, nullptr);
	}

	void PointLightSystem::createPipelineLayout(VkDescriptorSetLayout globalsetlayout) {
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(PointLightPushConstants);

		std::vector<VkDescriptorSetLayout> descriptorsetlayout{ globalsetlayout };

		VkPipelineLayoutCreateInfo pipelinelayoutInfo{};
		pipelinelayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelinelayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorsetlayout.size());
		pipelinelayoutInfo.pSetLayouts = descriptorsetlayout.data();
		pipelinelayoutInfo.pushConstantRangeCount = 1;
		pipelinelayoutInfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(m_Instance.getVkLogicalDevice(), &pipelinelayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline layout");
	}

	void PointLightSystem::createPipeline(VkRenderPass renderpass) {
		assert(m_pipelineLayout != nullptr && "cannot create pipeline before pipeline layout");

		Pipeline::PipelineConfiginfo pipelineConfig{};
		Pipeline::defaultPipelineConfiginfo(pipelineConfig);
		Pipeline::enableAlphaBlending(pipelineConfig);
		pipelineConfig.m_AttributeDescriptions.clear();
		pipelineConfig.m_BindingDescriptions.clear();
		pipelineConfig.m_renderpass = renderpass;
		pipelineConfig.m_PipelineLayout = m_pipelineLayout;
		m_Pipeline = std::make_unique<Pipeline>(m_Instance, "vert.spv", "frag.spv", pipelineConfig);
	}

	void PointLightSystem::update(FrameInfo& frameinfo, GlobalUBO& ubo) {
		//by right loop through all gameobj for pointlight components
		ubo.m_vPointLights[0].m_Position = Vec4(0.f, 2.f, 0.f, 1.f);
		ubo.m_vPointLights[0].m_Color = Vec4(1.f, 1.f, 1.f, 1.f);//white light with intensity at w
	}

	void PointLightSystem::render(FrameInfo& frameinfo) {
		m_Pipeline->bind(frameinfo.commandBuffer);
		vkCmdBindDescriptorSets(frameinfo.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &frameinfo.globalDescriptorSet, 0, nullptr);

		//by right, loop through all gameobj for pointlight components
		PointLightPushConstants pushdata{};
		pushdata.m_Position = Vec4(0.f, 2.f, 0.f, 1.f);
		pushdata.m_Color = Vec4(1.f, 1.f, 1.f, 1.f);
		//pushdata.m_radius = 1.f;

		vkCmdPushConstants(frameinfo.commandBuffer, m_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PointLightPushConstants), &pushdata);
		//vkCmdDraw(frameinfo.commandBuffer, 6, 1, 0, 0);
	}
}