#include"Rendering/renderPass.h"
#include "Rendering/GraphicsManager.h"
namespace TDS {
	RenderPass::RenderPass(VkDevice device, const std::vector<AttachmentInfo>& attachments)
		:m_Device(device)
	{
		std::vector<VkAttachmentDescription> attachmentDescriptions;
		attachmentDescriptions.resize(attachments.size());

		int colorAttachmentLoadCount = 0;
		int depthStencilAttachmentLoadCount = 0;

		for (int i{ 0 }; i < attachmentDescriptions.size(); i++)
		{
			auto& attachmentDescription = attachmentDescriptions[i];
			if (attachments[i].framebufferAttachment->getAttachmentType() == RenderTargetType::RESOLVE)
			{
				assert(attachments[i].loadOP == VK_ATTACHMENT_LOAD_OP_DONT_CARE && "Resolve attachments should have VK_ATTACHMENT_STORE_OP_DONT_CARE");
			}

			attachmentDescription.format = attachments[i].framebufferAttachment->getAttachmentDescription()._format;
			attachmentDescription.samples = attachments[i].framebufferAttachment->getAttachmentDescription()._sampleCount;
			attachmentDescription.loadOp = attachments[i].loadOP;
			attachmentDescription.storeOp = attachments[i].storeOP;
			bool loadImageLayout = attachmentDescription.loadOp == VK_ATTACHMENT_LOAD_OP_LOAD;
			if (attachments[i].framebufferAttachment->getAttachmentType() == RenderTargetType::DEPTHSTENCIL)
			{
				attachmentDescription.stencilLoadOp = attachments[i].stencilLoadOP;
				attachmentDescription.stencilStoreOp = attachments[i].stencilStoreOP;
				loadImageLayout += attachmentDescription.stencilLoadOp == VK_ATTACHMENT_LOAD_OP_LOAD;
			}
			else
			{
				attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			}

			attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//loadImageLayout ? attachments[i].framebufferAttachment->getImageLayout() : VK_IMAGE_LAYOUT_UNDEFINED;
			attachmentDescription.finalLayout = attachments[i].framebufferAttachment->getAttachmentDescription()._imagelayout;

			if ((attachmentDescription.loadOp == VK_ATTACHMENT_LOAD_OP_LOAD) && (attachments[i].framebufferAttachment->getAttachmentType() == RenderTargetType::COLOR))
				colorAttachmentLoadCount++;
			if ((attachmentDescription.loadOp == VK_ATTACHMENT_LOAD_OP_LOAD) && (attachments[i].framebufferAttachment->getAttachmentType() == RenderTargetType::DEPTH || attachments[i].framebufferAttachment->getAttachmentType() == RenderTargetType::DEPTHSTENCIL))
				depthStencilAttachmentLoadCount++;
		}

		std::vector<VkAttachmentReference> colorAttachment{};
		std::vector<VkAttachmentReference> depthStencilAttachments{};
		std::vector<VkAttachmentReference> resolveAttachments{};

		VkSubpassDescription subpassDescription{};
		subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDescription.pColorAttachments = nullptr;
		subpassDescription.pDepthStencilAttachment = nullptr;
		subpassDescription.pResolveAttachments = nullptr;

		for (uint32_t i{ 0 }; i < attachments.size(); i++)
		{
			VkAttachmentReference attachmentRef{};
			switch (attachments[i].framebufferAttachment->getAttachmentType()){
			case(RenderTargetType::COLOR):
				attachmentRef = { i, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
				colorAttachment.push_back(attachmentRef); break;
			case(RenderTargetType::DEPTH):
			case(RenderTargetType::DEPTHSTENCIL):
					attachmentRef = { i, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };
					depthStencilAttachments.push_back(attachmentRef); break;
			case(RenderTargetType::RESOLVE):
				attachmentRef = { i, attachments[i].framebufferAttachment->getImageLayout() };
				resolveAttachments.push_back(attachmentRef); break;

			}
		}


		subpassDescription.colorAttachmentCount = static_cast<uint32_t>(colorAttachment.size());
		if (colorAttachment.size() > 0) subpassDescription.pColorAttachments = colorAttachment.data();
		if (depthStencilAttachments.size() > 0) subpassDescription.pDepthStencilAttachment = depthStencilAttachments.data();
		if (resolveAttachments.size() > 0) subpassDescription.pResolveAttachments = resolveAttachments.data();


		// Subpass dependencies for layout transitions
		std::array<VkSubpassDependency, 2> dependencies{};

		dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[0].dstSubpass = 0;
		dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		dependencies[1].srcSubpass = 0;
		dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
		if (attachments.size() > 0) {
			dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

			dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;

			if (colorAttachment.size() > 0) {
				dependencies[0].dstAccessMask |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				dependencies[0].dstStageMask |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			}
			if (depthStencilAttachments.size() > 0) {
				dependencies[0].dstAccessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				dependencies[0].dstStageMask |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			}

			if (colorAttachmentLoadCount > 0) {
				//dependencies[0].srcAccessMask |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				dependencies[0].dstAccessMask |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			}
			if (depthStencilAttachmentLoadCount > 0) {
				dependencies[0].srcAccessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				dependencies[0].dstAccessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			}

			dependencies[1].srcStageMask = dependencies[0].dstStageMask;
			dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependencies[1].srcAccessMask = dependencies[0].dstAccessMask;
			dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		}
		else {
			dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			dependencies[0].srcAccessMask = VK_ACCESS_NONE;
			dependencies[0].dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			dependencies[0].dstAccessMask = VK_ACCESS_NONE;
			dependencies[1].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			dependencies[1].srcAccessMask = VK_ACCESS_NONE;
			dependencies[1].dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			dependencies[1].dstAccessMask = VK_ACCESS_NONE;
		}
		// Create the actual renderpass
		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachmentDescriptions.size());
		renderPassInfo.pAttachments = attachmentDescriptions.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpassDescription;
		renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
		renderPassInfo.pDependencies = dependencies.data();

		VK_ASSERT(vkCreateRenderPass(m_Device, &renderPassInfo, nullptr, &m_RenderPass), "Failed to create render pass");

		m_clearValues.resize(attachments.size());
		for (int i = 0; i < attachments.size(); i++) {
			switch (attachments[i].framebufferAttachment->getAttachmentType()) {
			case(RenderTargetType::COLOR):
				m_clearValues[i].color = attachments[i].clear.color;
				break;
			case(RenderTargetType::DEPTH):
			case(RenderTargetType::DEPTHSTENCIL):
				m_clearValues[i].depthStencil = attachments[i].clear.depth;
				break;
				// Resolve attachments must be loaded with VK_LOAD_OP_DONT_CARE
			}
		}


	}
	RenderPass::~RenderPass()
	{
		vkDestroyRenderPass(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice(), m_RenderPass, nullptr);
	}
	void RenderPass::beginRenderPass(VkCommandBuffer commandBuffer, FrameBuffer* framebuffer, uint32_t viewports)
	{
		assert(viewports > 0 && "You must have at least 1 viewport");
		
		VkRenderPassBeginInfo renderPassBeginInfo{};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.renderPass = m_RenderPass;
		renderPassBeginInfo.framebuffer = framebuffer->getVKFrameBuffer();
		renderPassBeginInfo.renderArea.extent.width = static_cast<uint32_t>(framebuffer->getDimensions().x);
		renderPassBeginInfo.renderArea.extent.height = static_cast<uint32_t>(framebuffer->getDimensions().y);
		renderPassBeginInfo.clearValueCount = m_clearValues.size();
		renderPassBeginInfo.pClearValues = m_clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.f;
		viewport.y = 0.f;
		viewport.width = framebuffer->getDimensions().x;
		viewport.height = framebuffer->getDimensions().y;
		viewport.minDepth = 0.f;
		viewport.maxDepth = 1.f;

		VkRect2D scissor{};
		scissor.extent.width = framebuffer->getDimensions().x;
		scissor.extent.height = framebuffer->getDimensions().y;
		scissor.offset.x = 0;
		scissor.offset.y = 0;

		if (viewports == 1)
		{
			vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
			vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
		}
		else
		{
			std::vector<VkViewport> viewportArray = std::vector<VkViewport>(viewports, viewport);
			std::vector<VkRect2D> scissorArray = std::vector<VkRect2D>(viewports, scissor);
			vkCmdSetViewport(commandBuffer, 0, viewports, viewportArray.data());
			vkCmdSetScissor(commandBuffer, 0, viewports, scissorArray.data());
		}

	}
	void RenderPass::endRenderPass(VkCommandBuffer commandBuffer)
	{
		vkCmdEndRenderPass(commandBuffer);
	}
}//End TDS