#include "Rendering/RenderTarget.h"
#include "Logger/Logger.h"
#include "Rendering/GraphicsManager.h"
namespace TDS
{
	RenderTarget::RenderTarget(std::shared_ptr<VulkanInstance> inst, const RenderTargetCI& attachmentCI)
		:m_Inst(inst), m_AttachmentDescription(attachmentCI), m_InheritsVkImage(attachmentCI._inheritVkImage)
	{
		create(inst, attachmentCI);
	}
	RenderTarget::~RenderTarget()
	{
		destroy();
	}
	void RenderTarget::create(std::shared_ptr<VulkanInstance> inst, const RenderTargetCI& attachmentCI)
	{
		if (!m_InheritsVkImage)
		{
			VkImageCreateInfo imageCI{};
			imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageCI.pNext = nullptr;
			imageCI.imageType = VK_IMAGE_TYPE_2D;
			imageCI.format = attachmentCI._format;
			imageCI.extent.width = static_cast<uint32_t>(attachmentCI._dim.x);
			imageCI.extent.height = static_cast<uint32_t>(attachmentCI._dim.y);
			imageCI.extent.depth = static_cast<uint32_t>(attachmentCI._dim.z);
			imageCI.mipLevels = attachmentCI._mipLevels;
			imageCI.arrayLayers = attachmentCI._layerCount;
			imageCI.samples = attachmentCI._sampleCount;
			imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
			imageCI.usage = attachmentCI._imageUsage;
			imageCI.flags = 0;//|= attachmentCI._viewType == VK_IMAGE_VIEW_TYPE_CUBE ? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT : 0;

			VkMemoryAllocateInfo memAlloc{};
			memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			VkMemoryRequirements memReqs;

			VK_ASSERT(vkCreateImage(inst->getVkLogicalDevice(), &imageCI, nullptr, &m_Image), "Failed to create image!");
			vkGetImageMemoryRequirements(inst->getVkLogicalDevice(), m_Image, &memReqs);
			m_MemSize = memAlloc.allocationSize = memReqs.size;
			memAlloc.memoryTypeIndex = inst->findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			if (vkAllocateMemory(inst->getVkLogicalDevice(), &memAlloc, nullptr, &m_ImageMem) != VK_SUCCESS) {
				TDS_ERROR("Ran out of memory!");
				return;
			}
			VK_ASSERT(vkBindImageMemory(inst->getVkLogicalDevice(), m_Image, m_ImageMem, 0), "Failed to bind memory!");


			VkImageViewCreateInfo imageViewCI{};
			imageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewCI.viewType = attachmentCI._viewType;
			imageViewCI.format = attachmentCI._format;
			
			m_SubResourceRange.aspectMask = attachmentCI._imageAspect;
			m_SubResourceRange.baseMipLevel = 0;
			m_SubResourceRange.levelCount = attachmentCI._mipLevels;
			m_SubResourceRange.baseArrayLayer = 0;
			m_SubResourceRange.layerCount = attachmentCI._layerCount;

			imageViewCI.subresourceRange = m_SubResourceRange;
			imageViewCI.image = m_Image;

			switch (attachmentCI._format) {
			case(VK_FORMAT_R8_UNORM):
			case(VK_FORMAT_R16_UNORM):
			case(VK_FORMAT_R16_SFLOAT):
			case(VK_FORMAT_D16_UNORM):
			case(VK_FORMAT_D16_UNORM_S8_UINT):
			case(VK_FORMAT_D32_SFLOAT):
			case(VK_FORMAT_D32_SFLOAT_S8_UINT):
				imageViewCI.components.r = VK_COMPONENT_SWIZZLE_R;
				imageViewCI.components.g = VK_COMPONENT_SWIZZLE_R;
				imageViewCI.components.b = VK_COMPONENT_SWIZZLE_R;
			}
			VK_ASSERT(vkCreateImageView(inst->getVkLogicalDevice(), &imageViewCI, nullptr, &m_ImageView), "Failed to create image view!");

		}
		else{

			m_Image = attachmentCI._inheritVkImage;
		}

		switch (attachmentCI._format) {
		case(VK_FORMAT_D16_UNORM_S8_UINT):
		case(VK_FORMAT_D32_SFLOAT_S8_UINT):
			VkImageViewCreateInfo imageViewStencilCreateInfo = {};
			imageViewStencilCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewStencilCreateInfo.viewType = attachmentCI._viewType;
			imageViewStencilCreateInfo.format = attachmentCI._format;
			m_SubResourceRange.aspectMask = VK_IMAGE_ASPECT_STENCIL_BIT;
			m_SubResourceRange.baseMipLevel = 0;
			m_SubResourceRange.levelCount = attachmentCI._mipLevels;
			m_SubResourceRange.baseArrayLayer = 0;
			m_SubResourceRange.layerCount = attachmentCI._layerCount;
			imageViewStencilCreateInfo.subresourceRange = m_SubResourceRange;
			imageViewStencilCreateInfo.image = m_Image;
			VK_ASSERT(vkCreateImageView(inst->getVkLogicalDevice(), &imageViewStencilCreateInfo, nullptr, &m_ImageViewSB), "Failed to create image view!");

			break;
		}

		m_RenderImageViews.resize(attachmentCI._overrideDirectLayer ? 1 : attachmentCI._layerCount);
		m_RenderSubRR.resize(attachmentCI._overrideDirectLayer ? 1 : attachmentCI._layerCount);
		for (int i{ 0 }; i < m_RenderImageViews.size(); i++) {
			m_RenderImageViews[i].resize(attachmentCI._mipLevels);
			m_RenderSubRR[i].resize(attachmentCI._mipLevels);
			for (int j{ 0 }; j < m_RenderImageViews[i].size(); j++)
			{
				VkImageViewCreateInfo subImageViewCreateInfo = {};
				subImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				subImageViewCreateInfo.viewType = attachmentCI._overrideDirectLayer ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_2D;
				subImageViewCreateInfo.format = attachmentCI._format;
				m_RenderSubRR[i][j].aspectMask = attachmentCI._imageAspect;
				m_RenderSubRR[i][j].baseMipLevel = j;
				m_RenderSubRR[i][j].levelCount = 1;
				m_RenderSubRR[i][j].baseArrayLayer = i;
				m_RenderSubRR[i][j].layerCount = attachmentCI._overrideDirectLayer ? attachmentCI._layerCount : 1;
				subImageViewCreateInfo.subresourceRange = m_RenderSubRR[i][j];
				subImageViewCreateInfo.image = m_Image;

				VK_ASSERT(vkCreateImageView(inst->getVkLogicalDevice(), &subImageViewCreateInfo, nullptr, &m_RenderImageViews[i][j]), "Failed to create render image view!");
			}
		}

		if (!m_InheritsVkImage) {
			if (attachmentCI._imageUsage & VK_IMAGE_USAGE_SAMPLED_BIT) {
				// Create sampler to sample from the attachment in the fragment shader
				VkSamplerCreateInfo samplerInfo = {};
				samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				samplerInfo.magFilter = attachmentCI._linearFiltering ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
				samplerInfo.minFilter = attachmentCI._linearFiltering ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
				samplerInfo.mipmapMode = attachmentCI._linearFiltering ? VK_SAMPLER_MIPMAP_MODE_LINEAR : VK_SAMPLER_MIPMAP_MODE_NEAREST;
				samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
				samplerInfo.mipLodBias = 0.0f;
				samplerInfo.maxAnisotropy = 1.0f;
				samplerInfo.minLod = 0.0f;
				samplerInfo.maxLod = static_cast<float>(attachmentCI._mipLevels);
				samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
				samplerInfo.addressModeV = samplerInfo.addressModeU;
				samplerInfo.addressModeW = samplerInfo.addressModeU;
				samplerInfo.compareEnable = attachmentCI._enablePCFSampler;
				samplerInfo.compareOp = VK_COMPARE_OP_LESS;

				VK_ASSERT(vkCreateSampler(inst->getVkLogicalDevice(), &samplerInfo, nullptr, &m_Sampler), "Failed to create sampler");
			}
		}
		m_Dimensions = { attachmentCI._dim.x, attachmentCI._dim.y,attachmentCI._dim.z };

	}
	void RenderTarget::resize(Vec3 newDim)
	{
		if (newDim == m_AttachmentDescription._dim) return; // in case already been resized
		destroy();
		m_AttachmentDescription._dim = newDim;
		create(m_Inst, m_AttachmentDescription);
	}
	void RenderTarget::destroy()
	{
		vkDeviceWaitIdle(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice());
		for (int i = 0; i < m_RenderImageViews.size(); i++) {
			for (int j = 0; j < m_RenderImageViews[i].size(); j++) {
				vkDestroyImageView(m_Inst->getVkLogicalDevice(), m_RenderImageViews[i][j], nullptr);
			}
		}

		if (!m_InheritsVkImage) {
			if (m_Sampler) {
				vkDestroySampler(m_Inst->getVkLogicalDevice(), m_Sampler, nullptr);
			}
			vkDestroyImageView(m_Inst->getVkLogicalDevice(), m_ImageView, nullptr);
			vkDestroyImage(m_Inst->getVkLogicalDevice(), m_Image, nullptr);
			vkFreeMemory(m_Inst->getVkLogicalDevice(), m_ImageMem, nullptr);
		}


	}
}