#include "vulkanTools/FrameBuffer.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/Renderer.h"
#include "vulkanTools/VulkanTexture.h"
namespace TDS
{



	void FrameBuffer::Resize(VkExtent2D newExtent)
	{
		Destroy();
		CreateFrameBuffer(newExtent.width, newExtent.height);

	}
	void FrameBuffer::SetClearColor(const iColor& color)
	{
		for (auto& attach : m_ClearAttachments)
			attach.clearValue = { {color.m_RGBA.x, color.m_RGBA.y, color.m_RGBA.y, color.m_RGBA.z} };

	}
	void FrameBuffer::CreateSampler(VkFilter filter)
	{
		VulkanInstance& inst = GraphicsManager::getInstance().getVkInstance();

		VkSamplerCreateInfo samplerCI = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };


		samplerCI.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerCI.magFilter = filter;
		samplerCI.minFilter = filter;
		samplerCI.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerCI.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		samplerCI.addressModeV = samplerCI.addressModeU;
		samplerCI.addressModeW = samplerCI.addressModeU;
		samplerCI.mipLodBias = 0.0f;
		samplerCI.maxAnisotropy = 1.0f;
		samplerCI.minLod = 0.0f;
		samplerCI.maxLod = 1.0f;
		samplerCI.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		samplerCI.maxAnisotropy = 1.0f;

		VkPhysicalDeviceFeatures features{};
		vkGetPhysicalDeviceFeatures(inst.getVkPhysicalDevice(), &features);

		if (features.samplerAnisotropy)
		{
			VkPhysicalDeviceProperties properties{};
			vkGetPhysicalDeviceProperties(inst.getVkPhysicalDevice(), &properties);
			samplerCI.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
			samplerCI.anisotropyEnable = VK_TRUE;
		}

		VK_ASSERT(vkCreateSampler(inst.getVkLogicalDevice(), &samplerCI, nullptr, &m_Sampler), "Failed to create fb sampler!");

	}
	void FrameBuffer::DestroyAttachment(FBAttachment& fbAttachmnet)
	{
		VulkanInstance& inst = GraphicsManager::getInstance().getVkInstance();
		if (fbAttachmnet.m_View)
		{
			vkDestroyImageView(inst.getVkLogicalDevice(), fbAttachmnet.m_View, 0);
			fbAttachmnet.m_View = 0;
		}

		if (fbAttachmnet.m_Image)
		{
			GraphicsAllocator::FreeBuffer(fbAttachmnet.m_Image, fbAttachmnet.m_Allocation);
			fbAttachmnet.m_Image = 0;
			fbAttachmnet.m_Allocation = 0;
		}
	}

	void FrameBuffer::CreateAttachment(VkFormat format, FBAttachment& attachment, VkExtent2D extent, VkSampleCountFlagBits sampleCnt, VkImageUsageFlags usage, VkImageAspectFlags imageAspect)
	{
		VulkanInstance& inst = GraphicsManager::getInstance().getVkInstance();

		CreateImageParams params{};
		params.m_Format = format;
		params.m_tiling = VK_IMAGE_TILING_OPTIMAL;
		params.m_usage = usage;

		attachment.m_Image = VulkanTexture::CreateVulkanImage(extent, 1, sampleCnt, params, attachment.m_Allocation);

		VkImageViewCreateInfo colorImageViewCI = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		colorImageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
		colorImageViewCI.format = format;
		colorImageViewCI.components.r = VK_COMPONENT_SWIZZLE_R;
		colorImageViewCI.components.g = VK_COMPONENT_SWIZZLE_G;
		colorImageViewCI.components.b = VK_COMPONENT_SWIZZLE_B;
		colorImageViewCI.components.a = VK_COMPONENT_SWIZZLE_A;
		colorImageViewCI.subresourceRange = {};
		colorImageViewCI.subresourceRange.aspectMask = imageAspect;
		colorImageViewCI.subresourceRange.baseMipLevel = 0;
		colorImageViewCI.subresourceRange.baseArrayLayer = 0;
		colorImageViewCI.subresourceRange.levelCount = 1;
		colorImageViewCI.subresourceRange.layerCount = 1;
		colorImageViewCI.image = attachment.m_Image;

		VK_ASSERT(vkCreateImageView(inst.getVkLogicalDevice(), &colorImageViewCI, nullptr, &attachment.m_View), "Fail to create attachment view!");


	}

	void FrameBuffer::CreateRenderPass(VkRenderPass& output, VkFormat clrFormat, VkFormat depthFormat, VkSampleCountFlagBits sampleCnt,
		std::uint32_t numOfAttachments, std::uint32_t numOfResolveAttachments,
		std::uint32_t numOfDepthAttachments)
	{
		std::vector<VkAttachmentReference> colorRef(numOfAttachments);
		std::vector<VkAttachmentReference> depthRef(numOfDepthAttachments);
		std::vector<VkAttachmentReference> resolveRef(numOfResolveAttachments);

		std::vector<VkAttachmentDescription> attachments(numOfAttachments + numOfDepthAttachments + numOfResolveAttachments);

		std::uint32_t itrCnt = 0;
		for (std::uint32_t i = 0; i < numOfAttachments; ++itrCnt, ++i)
		{

			colorRef[i].attachment = itrCnt;
			colorRef[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


			VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			if (m_Entry.m_AttachmentRequirememnts[i].m_ClearOp)
				loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;

			VkImageLayout layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

			attachments[itrCnt].format = m_Entry.m_AttachmentRequirememnts[i].m_Format;
			attachments[itrCnt].samples = sampleCnt;
			attachments[itrCnt].loadOp = loadOp;
			attachments[itrCnt].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachments[itrCnt].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachments[itrCnt].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachments[itrCnt].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			attachments[itrCnt].finalLayout = layout;
		}

		for (std::uint32_t i = 0; i < numOfResolveAttachments; ++itrCnt, ++i)
		{
			VkImageLayout layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

			VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			if (!m_Entry.m_AttachmentRequirememnts[i].m_ClearOp)
				loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;

			attachments[itrCnt].format = m_Entry.m_AttachmentRequirememnts[i].m_Format;
			attachments[itrCnt].samples = VK_SAMPLE_COUNT_1_BIT;
			attachments[itrCnt].loadOp = loadOp;
			attachments[itrCnt].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachments[itrCnt].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			attachments[itrCnt].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachments[itrCnt].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			attachments[itrCnt].finalLayout = layout;

			resolveRef[i].attachment = itrCnt;
			resolveRef[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		for (std::uint32_t i = 0; i < numOfDepthAttachments; ++itrCnt, ++i)
		{
			attachments[itrCnt].format = m_DepthFormat;
			attachments[itrCnt].samples = sampleCnt;
			attachments[itrCnt].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachments[itrCnt].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachments[itrCnt].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachments[itrCnt].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachments[itrCnt].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			attachments[itrCnt].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

			depthRef[i].attachment = itrCnt;
			depthRef[i].layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}
		VkSubpassDescription subpass = {};

		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = static_cast<uint32_t>(colorRef.size());
		subpass.pColorAttachments = colorRef.data();
		subpass.pDepthStencilAttachment = depthRef.data();

		std::vector<VkSubpassDependency> dependencies;
		//if (m_Entry.m_SyncLayout)
		//{
		//	dependencies.resize(2);
		//	dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
		//	dependencies[0].dstSubpass = 0;
		//	dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		//	dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		//	dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		//	dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		//	dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		//	dependencies[1].srcSubpass = 0;
		//	dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
		//	dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		//	dependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		//	dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		//	dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		//	dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
		//}

		VkRenderPassCreateInfo renderPassCI = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
		renderPassCI.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassCI.pAttachments = attachments.data();
		renderPassCI.subpassCount = 1;
		renderPassCI.pSubpasses = &subpass;
		renderPassCI.dependencyCount = static_cast<uint32_t>(dependencies.size());
		renderPassCI.pDependencies = dependencies.data();


		VK_ASSERT(vkCreateRenderPass(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice(),
			&renderPassCI, nullptr, &output), "Failed to create render pass for frame buffer!");

	}

	FBAttachment& FrameBuffer::GetDepthAttachment()
	{
		return m_DepthAttachment;
	}
	const std::uint32_t FrameBuffer::GetNumberOfAttachments() const
	{
		return std::uint32_t(m_Attachments.size());
	}

	VkRenderPass FrameBuffer::GetRenderPass() const
	{
		return m_RenderPass;
	}
	VkFramebuffer FrameBuffer::GetCurrentFrameBuffer() const
	{
		return m_FrameBuffers[m_FrameIndex];
	}
	VkFramebuffer FrameBuffer::GetFrameBuffer(std::uint32_t index) const
	{
		return m_FrameBuffers[index];
	}
	std::vector<VkClearValue>& FrameBuffer::GetClearValues()
	{
		return m_ClearValues;
	}
	std::vector<VkClearAttachment>& FrameBuffer::GetClearAttachments()
	{
		return m_ClearAttachments;
	}
	FrameBufferEntryInfo& FrameBuffer::getFBEntryInfo()
	{
		return m_Entry;
	}
}