/*!*************************************************************************
****
\file ShadowMap.cpp
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the ShadowMap Class
****************************************************************************
***/
#include "vulkanTools/ShadowMap.h"
#include "vulkanTools/Pipeline.h"

namespace TDS {
	ShadowMap::ShadowMap(VulkanInstance& Instance, VkRenderPass renderpass, VkDescriptorSetLayout globbalsetlayout)
		:m_Instance(Instance) {
		createPipeline(renderpass);
	}

	ShadowMap::~ShadowMap() {
		vkDestroyPipelineLayout(m_Instance.getVkLogicalDevice(), m_pipelineLayout, nullptr);
	}

	void ShadowMap::createImageView() {
		VkImageViewCreateInfo viewinfo{};
		viewinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewinfo.pNext = NULL;
		viewinfo.image = m_Image;
		viewinfo.format = VK_FORMAT_D32_SFLOAT;
		viewinfo.components.r = VK_COMPONENT_SWIZZLE_R;
		viewinfo.components.g = VK_COMPONENT_SWIZZLE_G;
		viewinfo.components.b = VK_COMPONENT_SWIZZLE_B;
		viewinfo.components.a = VK_COMPONENT_SWIZZLE_A;
		viewinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		viewinfo.subresourceRange.baseMipLevel = 0;
		viewinfo.subresourceRange.levelCount = 1;
		viewinfo.subresourceRange.baseArrayLayer = 0;
		viewinfo.subresourceRange.layerCount = 1;
		viewinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewinfo.flags = 0;

		VkImageView shadowmapview;
		if (vkCreateImageView(m_Instance.getVkLogicalDevice(), &viewinfo, NULL, &m_ImageView) != VK_SUCCESS)
			throw std::runtime_error("unable to create shadow map image view");
	}

	void ShadowMap::createImage() {
		VkImageCreateInfo Imageinfo{};
		Imageinfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		Imageinfo.pNext = NULL;
		Imageinfo.imageType = VK_IMAGE_TYPE_2D;
		Imageinfo.format = VK_FORMAT_D32_SFLOAT;
		Imageinfo.extent.width = SHADOW_MAP_WIDTH;//window height and width??
		Imageinfo.extent.height = SHADOW_MAP_HEIGHT;
		Imageinfo.extent.depth = 1;
		Imageinfo.mipLevels = 1;
		Imageinfo.arrayLayers = 1;
		Imageinfo.samples = VK_SAMPLE_COUNT_1_BIT;
		Imageinfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		Imageinfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		Imageinfo.queueFamilyIndexCount = 0;
		Imageinfo.pQueueFamilyIndices = NULL;
		Imageinfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		Imageinfo.flags = 0;

		//create image for shadow map??
		if (vkCreateImage(m_Instance.getVkLogicalDevice(), &Imageinfo, NULL, &m_Image) != VK_SUCCESS)
			throw std::runtime_error("unable to create shadow map image info");

	}

	void ShadowMap::createRenderPass() {
		VkAttachmentDescription attachments[2];

		//depth
		attachments[0].format = VK_FORMAT_D32_SFLOAT;
		attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		attachments[0].flags = 0;

		VkAttachmentReference depthref;
		depthref.attachment = 0;
		depthref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass[1];
		subpass[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass[0].flags = 0;
		subpass[0].inputAttachmentCount = 0;
		subpass[0].pInputAttachments = NULL;
		subpass[0].colorAttachmentCount = 0;
		subpass[0].pColorAttachments = NULL;
		subpass[0].pDepthStencilAttachment = &depthref;
		subpass[0].preserveAttachmentCount = 0;
		subpass[0].pPreserveAttachments = NULL;

		VkRenderPassCreateInfo rpinfo;
		rpinfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		rpinfo.pNext = NULL;
		rpinfo.attachmentCount = 1;
		rpinfo.pAttachments = attachments;
		rpinfo.subpassCount = 1;
		rpinfo.pSubpasses = subpass;
		rpinfo.dependencyCount = 0;
		rpinfo.pDependencies = NULL;
		rpinfo.flags = 0;

		if (vkCreateRenderPass(m_Instance.getVkLogicalDevice(), &rpinfo, NULL, &m_Renderpass) != VK_SUCCESS)
			throw std::runtime_error("unable to create renderpass for shadow map");
	}

	void ShadowMap::createFrameBuffer() {
		VkFramebufferCreateInfo fbinfo{};
		fbinfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		fbinfo.pNext = NULL;
		fbinfo.renderPass = m_Renderpass;
		fbinfo.attachmentCount = 1;
		fbinfo.pAttachments = &m_ImageView;
		fbinfo.width = SHADOW_MAP_WIDTH;
		fbinfo.height = SHADOW_MAP_HEIGHT;
		fbinfo.layers = 1;
		fbinfo.flags = 0;

		if (vkCreateFramebuffer(m_Instance.getVkLogicalDevice(), &fbinfo, NULL, &m_FrameBuffer) != VK_SUCCESS)
			throw std::runtime_error("unable to create shadow map fbo");
	}

	void ShadowMap::createPipeline(VkRenderPass renderpass) {
		/*Pipeline::PipelineConfiginfo pipelineconfig;
		Pipeline::defaultPipelineConfiginfo(pipelineconfig);
		Pipeline::enableAlphaBlending(pipelineconfig);
		m_Pipeline = std::make_unique<Pipeline>(m_Instance, "shadowvert.spv", "shadowfrag.spv", pipelineconfig);*/
		auto vertcode = Pipeline::ReadFile("shadowmap.vert");
		m_Pipeline->createShaderModule(vertcode, &m_VertShader);

		VkPipelineShaderStageCreateInfo shaderstages[1];
		shaderstages[0].pNext = NULL;
		shaderstages[0].pSpecializationInfo = NULL;
		shaderstages[0].flags = 0;
		shaderstages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderstages[0].pName = "main";
		shaderstages[0].module = m_VertShader;

		VkVertexInputBindingDescription bindingDesc[1];
		VkVertexInputAttributeDescription attributeDesc[1];

		bindingDesc[0].binding = 0;
		bindingDesc[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		bindingDesc[0].stride = 2 * sizeof(Vec3);

		attributeDesc[0].binding = 0;
		attributeDesc[0].location = 0;
		attributeDesc[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDesc[0].offset = 0;

		VkPipelineVertexInputStateCreateInfo vertexinputinfo;
		vertexinputinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexinputinfo.pNext = NULL;
		vertexinputinfo.flags = 0;
		vertexinputinfo.vertexBindingDescriptionCount = 1;
		vertexinputinfo.pVertexBindingDescriptions = bindingDesc;
		vertexinputinfo.vertexAttributeDescriptionCount = 1;
		vertexinputinfo.pVertexAttributeDescriptions = attributeDesc;

		VkGraphicsPipelineCreateInfo Pipelineinfo;
		Pipelineinfo.pVertexInputState = &vertexinputinfo;
		Pipelineinfo.pStages = shaderstages;
		Pipelineinfo.stageCount = 1;

	}

	void ShadowMap::createCommandBuffer() {
		VkClearValue clearvalues[1];
		clearvalues[0].depthStencil.depth = 1.f;
		clearvalues[0].depthStencil.stencil = 0;

		VkRenderPassBeginInfo rpbegin;
		rpbegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		rpbegin.pNext = NULL;
		rpbegin.renderPass = m_Renderpass;
		rpbegin.framebuffer = m_FrameBuffer;
		rpbegin.renderArea.offset.x = 0;
		rpbegin.renderArea.offset.y = 0;
		rpbegin.renderArea.extent.width = SHADOW_MAP_WIDTH;
		rpbegin.renderArea.extent.height = SHADOW_MAP_HEIGHT;
		rpbegin.clearValueCount = 1;
		rpbegin.pClearValues = clearvalues;

		vkCmdBeginRenderPass(m_CmdBuffer, &rpbegin, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport;
		viewport.height = SHADOW_MAP_HEIGHT;
		viewport.width = SHADOW_MAP_WIDTH;
		viewport.minDepth = 0.f;
		viewport.maxDepth = 1.f;
		viewport.x = 0;
		viewport.y = 0;
		vkCmdSetViewport(m_CmdBuffer, 0, 1, &viewport);
		
		VkRect2D scissor;
		scissor.extent.width = SHADOW_MAP_WIDTH;
		scissor.extent.height = SHADOW_MAP_HEIGHT;
		scissor.offset.x = 0;
		scissor.offset.y = 0;
		vkCmdSetScissor(m_CmdBuffer, 0, 1, &scissor);
	}


}