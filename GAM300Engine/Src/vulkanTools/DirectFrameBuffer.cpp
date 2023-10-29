//#include "vulkanTools/DirectFrameBuffer.h"
//#include "Rendering/GraphicsManager.h"
//#include "vulkanTools/vulkanInstance.h"
//#include "vulkanTools/vulkanTexture.h"
//#include "vulkanTools/Renderer.h"
//#include "vulkanTools/CommandManager.h"
//namespace TDS
//{
//	DirectFrameBuffer::DirectFrameBuffer(FrameBufferEntryInfo& entry)
//	{
//		Init(entry);
//
//	}
//	DirectFrameBuffer::~DirectFrameBuffer()
//	{
//		Destroy();
//	}
//	bool DirectFrameBuffer::Init(FrameBufferEntryInfo& entryInfo)
//	{
//		Renderer& rdr = GraphicsManager::getInstance().GetSwapchainRenderer();
//		m_Entry = entryInfo;
//		m_ColorFormat = rdr.getSwapchain().GetSwapChainImageFormat();
//		m_DepthFormat = rdr.getSwapchain().findDepthFormat();
//		return CreateFrameBuffer(entryInfo.m_AreaDimension.width, entryInfo.m_AreaDimension.height);
//	}
//	void DirectFrameBuffer::Destroy()
//	{
//		VulkanInstance& instance = GraphicsManager::getInstance().getVkInstance();
//
//		if (m_Sampler)
//		{
//			vkDestroySampler(instance.getVkLogicalDevice(), m_Sampler, 0);
//			m_Sampler = nullptr;
//		}
//
//		if (m_RenderPass)
//		{
//			vkDestroyRenderPass(instance.getVkLogicalDevice(), m_RenderPass, 0);
//			m_RenderPass = nullptr;
//		}
//
//		for (auto& fb : m_FrameBuffers)
//		{
//			if (fb)
//			{
//				vkDestroyFramebuffer(instance.getVkLogicalDevice(), fb, 0);
//				fb = nullptr;
//			}
//		}
//		m_FrameBuffers.clear();
//
//		DestroyAttachment(m_DepthAttachment);
//
//		for (auto& colorAttach : m_Attachments)
//		{
//			DestroyAttachment(colorAttach);
//		}
//
//		m_Attachments.clear();
//
//		for (auto& resolve : m_ResolveAttachment)
//		{
//			DestroyAttachment(resolve);
//		}
//
//		m_ResolveAttachment.clear();
//
//	}
//	bool DirectFrameBuffer::CreateFrameBuffer(std::uint32_t width, std::uint32_t height)
//	{
//		if (m_Entry.m_AttachmentRequirememnts.size() > 1 || m_Entry.m_AttachmentRequirememnts.empty())
//		{
//			TDS_WARN("Failed to create frame buffer...\n");
//			return false;
//		}
//
//		m_Entry.m_AreaDimension = { width, height };
//		std::uint32_t numberOfFrameBuffers = std::uint32_t(m_Entry.m_AttachmentRequirememnts.size());
//		std::uint32_t attachmentCnt = numberOfFrameBuffers + 1;
//
//		m_Attachments.resize(numberOfFrameBuffers);
//		m_ClearValues.resize(attachmentCnt);
//		m_ClearAttachments.resize(attachmentCnt);
//
//		std::vector<VkImageView> attach(attachmentCnt);
//
//		CommandBufferInfo singleExecution{};
//		CommandManager& cmdMgr = GraphicsManager::getInstance().getCommandManager();
//
//		cmdMgr.CreateSingleUseCommandBuffer(singleExecution);
//
//		CreateSampler(m_Entry.m_Filter);
//		//Create color
//		std::uint32_t attachmentIndex = 0;
//		for (std::uint32_t i = 0; i < numberOfFrameBuffers; ++attachmentIndex, ++i)
//		{
//			VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
//			CreateAttachment(m_Entry.m_AttachmentRequirememnts[i].m_Format, m_Attachments[i], { width, height }, VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT, usage, VK_IMAGE_ASPECT_COLOR_BIT);
//
//			m_Attachments[i].m_ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//			m_Attachments[i].m_ImageInfo.imageView = m_Attachments[i].m_View;
//			m_Attachments[i].m_ImageInfo.sampler = m_Sampler;
//
//			ImageMemoryLayoutInput input{};
//			input.m_subResourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
//			input.m_subResourceRange.baseMipLevel = 0;
//			input.m_subResourceRange.levelCount = 1;
//			input.m_subResourceRange.layerCount = 1;
//			input.m_oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//			input.m_NewLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//			input.m_Image = m_Attachments[i].m_Image;
//			VulkanTexture::setTextureLayout(singleExecution.m_CommandBuffer.m_CmdBuffer, input);
//			attach[attachmentIndex] = m_Attachments[i].m_View;
//			m_ClearValues[attachmentIndex].color = { {m_Entry.m_AttachmentRequirememnts[i].m_ClearColor.m_RGBA.x, m_Entry.m_AttachmentRequirememnts[i].m_ClearColor.m_RGBA.y,
//				m_Entry.m_AttachmentRequirememnts[i].m_ClearColor.m_RGBA.z, m_Entry.m_AttachmentRequirememnts[i].m_ClearColor.m_RGBA.w} };
//			m_ClearAttachments[attachmentIndex].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
//			m_ClearAttachments[attachmentIndex].clearValue = m_ClearValues[attachmentIndex];
//			m_ClearAttachments[attachmentIndex].colorAttachment = attachmentIndex;
//
//		}
//
//		//Create depth
//		VkImageUsageFlags usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
//		VkImageAspectFlags imageAspect = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
//		CreateAttachment(m_DepthFormat, m_DepthAttachment, { width, height }, VK_SAMPLE_COUNT_1_BIT, usage, imageAspect);
//
//		attach[attachmentIndex] = m_DepthAttachment.m_View;
//
//		m_ClearValues[attachmentIndex].depthStencil = { 1.f , 0 };
//		m_ClearAttachments[attachmentIndex].aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
//		m_ClearAttachments[attachmentIndex].clearValue.depthStencil = { 1.f, 0 };
//
//		if (m_RenderPass == nullptr)
//			CreateRenderPass(m_RenderPass, m_ColorFormat, m_DepthFormat, VK_SAMPLE_COUNT_1_BIT, std::uint32_t(m_Attachments.size()));
//
//		VkFramebufferCreateInfo fbufCreateInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
//		fbufCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
//		fbufCreateInfo.pNext = NULL;
//		fbufCreateInfo.renderPass = m_RenderPass;
//		fbufCreateInfo.attachmentCount = static_cast<uint32_t>(attach.size());
//		fbufCreateInfo.pAttachments = attach.data();
//		fbufCreateInfo.width = width;
//		fbufCreateInfo.height = height;
//		fbufCreateInfo.layers = 1;
//
//		cmdMgr.EndExecution(singleExecution);
//
//		m_FrameBuffers.resize(1);
//		VkDevice device = GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice();
//		VK_ASSERT(vkCreateFramebuffer(device, &fbufCreateInfo, 0, &m_FrameBuffers[0]), "Successfully created frame buffer");
//		return true;
//
//
//	}
//}