#include "vulkanTools/FrameBuffer.h"
#include "Rendering/GraphicsManager.h"
namespace TDS
{
	
	FrameBuffer::FrameBuffer(VkDevice _device, VkRenderPass _renderPass, const std::vector<RenderTarget*>& _attachments, uint32_t _layer, uint32_t _mipLevel)
		:m_device(_device),m_UseLayer(_layer),m_UseMipLevel(_mipLevel), m_renderPass(_renderPass)
	
	{
		create(_device, _renderPass, _attachments);
		m_Attachments.reserve(_attachments.size());
		for (RenderTarget* attachment : _attachments)
			m_Attachments.push_back(attachment);
	}

	FrameBuffer::FrameBuffer(VkDevice _device, VkRenderPass _renderPass, [[maybe_unused]] bool _imageless, Vec3 _ImageLessDim)
		:m_device(_device),m_UseLayer(0), m_UseMipLevel(0), m_renderPass(_renderPass)
	{
		m_Width = static_cast<uint32_t>(_ImageLessDim.x);
		m_Height = static_cast<uint32_t>(_ImageLessDim.y);
		m_Depth = static_cast<uint32_t>(_ImageLessDim.z);
		createImageless(_device, _renderPass);
	}

	FrameBuffer::~FrameBuffer()
	{
		destroy();
	}

	void FrameBuffer::resize(Vec3 _newdim, VkRenderPass _renderPass)
	{
		for (RenderTarget* attach : m_Attachments)
			attach->resize(_newdim);

		destroy();
		create(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice(), _renderPass, m_Attachments);

	}

	void FrameBuffer::create(VkDevice _device, VkRenderPass _renderPass, const std::vector<RenderTarget*>& _attachments)
	{
		std::vector<VkImageView> imageViews;
		int lowestLayerCounterOverride = -1;
		for (auto& attachment : _attachments)
		{
			if (attachment->getAttachmentDescription()._overrideDirectLayer)
			{
				lowestLayerCounterOverride == -1 ? lowestLayerCounterOverride = static_cast<int>(attachment->getAttachmentDescription()._layerCount) :
					lowestLayerCounterOverride = std::min(lowestLayerCounterOverride, static_cast<int>(attachment->getAttachmentDescription()._layerCount));
			}
			imageViews.push_back(attachment->getRenderImageView(m_UseLayer, m_UseMipLevel));
		}

		if (lowestLayerCounterOverride == -1)
			lowestLayerCounterOverride = 1;

		m_Width = static_cast<uint32_t>(_attachments[0]->getDimensions().x / Mathf::Pow(2.f, static_cast<float>(m_UseMipLevel)));
		m_Height = static_cast<uint32_t>(_attachments[0]->getDimensions().y / Mathf::Pow(2.f, static_cast<float>(m_UseMipLevel)));
		m_Depth = static_cast<uint32_t>(_attachments[0]->getDimensions().z);

		VkFramebufferCreateInfo framebufferCI{
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.renderPass = _renderPass,
			.attachmentCount = static_cast<uint32_t>(imageViews.size()),
			.pAttachments = imageViews.data(),
			.width = m_Width,
			.height = m_Height,
			.layers = static_cast<uint32_t>(lowestLayerCounterOverride)
		};

		VK_ASSERT(vkCreateFramebuffer(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice(), &framebufferCI, nullptr, &m_FrameBuffer), "Failed to create FrameBuffer!");



	}

	void FrameBuffer::createImageless(VkDevice& _device, VkRenderPass _renderPass)
	{

		VkFramebufferAttachmentsCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO;
		createInfo.attachmentImageInfoCount = 0;
		createInfo.pAttachmentImageInfos = nullptr;


		VkFramebufferCreateInfo framebufferCI{};
		framebufferCI.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCI.pNext = &createInfo;
		framebufferCI.flags = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT;
		framebufferCI.renderPass = _renderPass;
		framebufferCI.attachmentCount = 0;
		framebufferCI.pAttachments = nullptr;
		framebufferCI.width = m_Width;
		framebufferCI.height = m_Height;
		framebufferCI.layers = 1;

		VK_ASSERT(vkCreateFramebuffer(_device, &framebufferCI, nullptr, &m_FrameBuffer), "Failed to create framebuffer!");

	}

	void FrameBuffer::destroy()
	{
		vkDeviceWaitIdle(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice());
		vkDestroyFramebuffer(GraphicsManager::getInstance().getVkInstance().getVkLogicalDevice(), m_FrameBuffer, nullptr);
		

	}

}