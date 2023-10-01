/*!*************************************************************************
****
\file RendererManager.cpp
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the RendererManager Class
****************************************************************************
***/
#include "vulkanTools/RendererManager.h"

namespace TDS {
	RendererManager::RendererManager(VulkanInstance& instance, VkRenderPass renderpass, VkDescriptorSetLayout globalsetlayout) : m_Instance{ instance } {
		createPipelineLayout(globalsetlayout);
		createPipeline(renderpass);
	}

	RendererManager::~RendererManager() {
		vkDestroyPipelineLayout(m_Instance.getVkLogicalDevice(), m_PipelineLayout, nullptr);
	}

	void RendererManager::createPipelineLayout(VkDescriptorSetLayout globalsetlayout) {
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushConstantData);

		std::vector<VkDescriptorSetLayout> descriptorsetlayouts{ globalsetlayout };

		VkPipelineLayoutCreateInfo pipelinelayoutinfo{};
		pipelinelayoutinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelinelayoutinfo.setLayoutCount = static_cast<uint32_t>(descriptorsetlayouts.size());
		pipelinelayoutinfo.pSetLayouts = descriptorsetlayouts.data();
		pipelinelayoutinfo.pushConstantRangeCount = 1;
		pipelinelayoutinfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(m_Instance.getVkLogicalDevice(), &pipelinelayoutinfo, nullptr, &m_PipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline layout");
	}

	void RendererManager::createPipeline(VkRenderPass renderpass) {
		assert(m_PipelineLayout != nullptr && "cannot create pipeline before pipeline layout");

		Pipeline::PipelineConfiginfo pipelineconfig{};
		Pipeline::defaultPipelineConfiginfo(pipelineconfig);
		pipelineconfig.m_renderpass = renderpass;
		pipelineconfig.m_PipelineLayout = m_PipelineLayout;
		m_Pipeline = std::make_unique<Pipeline>(m_Instance, "vert.spv", "frag.spv", pipelineconfig);
	}

	void RendererManager::draw(FrameInfo& frameinfo) {
		m_Pipeline->bind(frameinfo.commandBuffer);

		vkCmdBindDescriptorSets(frameinfo.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_PipelineLayout, 0, 1, &frameinfo.globalDescriptorSet, 0, nullptr);

		//renderloop per frame
		/*for (auto& kv : frameinfo.gameObjects) {
			auto& obj = kv.second;
			if (obj.model == nullptr) continue;
			SimplePushConstantData push{};
			push.modelMatrix = obj.transform.mat4();
			push.normalMatrix = obj.transform.normalMatrix();

			vkCmdPushConstants(
				frameInfo.commandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(SimplePushConstantData),
				&push);*/

				//switch to ECS transform component
		SimplePushConstantData push{};
		Mat4 temp{ 1.0f, 0.f, 0.f, 0.f,
							0.f, 1.f, 0.f, 0.f,
							0.f, 0.f, 1.f, 0.f,
							0.f, 0.f, 0.f, 1.f };
		push.ModelMat = temp;
		temp.transpose();
		temp.inverse();
		push.NormalMat = temp;

		vkCmdPushConstants(frameinfo.commandBuffer, m_PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
			0, sizeof(SimplePushConstantData), &push);
		frameinfo.model.bind(frameinfo.commandBuffer);
		frameinfo.model.draw(frameinfo.commandBuffer);
		//}
	}
}