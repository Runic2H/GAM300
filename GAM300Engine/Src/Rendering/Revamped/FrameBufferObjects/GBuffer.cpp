#include "Rendering/Revamped/FrameBufferObjects/GBuffer.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/VulkanPipeline.h"
namespace TDS
{
	GBufferObject::GBufferObject(Vec2 DimensionInput)
	{
		m_Resizeable = true;
		m_AutoSync = true;
		m_TargetSwapchain = false;
		m_SampleCnt = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		m_FrameBufferDimension = DimensionInput;
		m_FBOType = FBO_TYPE::G_BUFFER;

		m_RenderAttachmentInfo.emplace_back(
			RenderTargetCI(VK_FORMAT_R8G8B8A8_UNORM,
				VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_VIEW_TYPE_2D,
				m_FrameBufferDimension,
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
				VK_IMAGE_USAGE_SAMPLED_BIT |
				VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				RenderTargetType::COLOR,
				false,
				VK_SAMPLE_COUNT_1_BIT)

		);

		m_RenderAttachmentInfo.emplace_back(
			RenderTargetCI(VK_FORMAT_R32_UINT,
				VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_VIEW_TYPE_2D,
				m_FrameBufferDimension,
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
				VK_IMAGE_USAGE_SAMPLED_BIT,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				RenderTargetType::COLOR,
				false,
				VK_SAMPLE_COUNT_1_BIT)

		);

		m_RenderAttachmentInfo.emplace_back(
			RenderTargetCI(VK_FORMAT_R32G32B32A32_SFLOAT,
				VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_VIEW_TYPE_2D,
				m_FrameBufferDimension,
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
				VK_IMAGE_USAGE_SAMPLED_BIT,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				RenderTargetType::COLOR,
				false,
				VK_SAMPLE_COUNT_1_BIT)

		);
		m_RenderAttachmentInfo.emplace_back(
			RenderTargetCI(VK_FORMAT_R16G16B16A16_SFLOAT,
				VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_VIEW_TYPE_2D,
				m_FrameBufferDimension,
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
				VK_IMAGE_USAGE_SAMPLED_BIT,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				RenderTargetType::COLOR,
				false,
				VK_SAMPLE_COUNT_1_BIT)

		);
	}
	bool GBufferObject::Create()
	{
		if (m_RenderAttachmentInfo.size() > 1 && m_TargetSwapchain
			|| m_RenderAttachmentInfo.empty())
			return false;

		GraphicsManager& mgr = GraphicsManager::getInstance();

		std::shared_ptr<VulkanInstance> instance = mgr.getVkInstancePtr();
		m_RenderTargets.resize(m_RenderAttachmentInfo.size());
		std::vector<AttachmentInfo> attachmentInfos{};


		std::uint32_t attachmentCnt = (std::uint32_t)m_RenderAttachmentInfo.size();
		std::uint32_t totalBufferSize = attachmentCnt + 1;
		attachmentInfos.resize(totalBufferSize);
		unsigned i = 0;
		for (; i < attachmentCnt; ++i)
		{
			m_RenderTargets[i] = new RenderTarget(instance, m_RenderAttachmentInfo[i]);
			attachmentInfos[i].framebufferAttachment = m_RenderTargets[i];
			attachmentInfos[i].loadOP = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachmentInfos[i].storeOP = VK_ATTACHMENT_STORE_OP_STORE;
			attachmentInfos[i].stencilLoadOP = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachmentInfos[i].stencilStoreOP = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		}

		VkFormat depthFormat = mgr.getVkInstance().CheckForValidDepthStencil(
			{ VK_FORMAT_D32_SFLOAT,
			 VK_FORMAT_D32_SFLOAT_S8_UINT,
			 VK_FORMAT_D24_UNORM_S8_UINT,
			 VK_FORMAT_D16_UNORM_S8_UINT,
			 VK_FORMAT_D16_UNORM }
		);


		RenderTargetCI depthInfo = RenderTargetCI(depthFormat,
			VK_IMAGE_ASPECT_DEPTH_BIT,
			VK_IMAGE_VIEW_TYPE_2D,
			m_FrameBufferDimension,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			RenderTargetType::DEPTH,
			false,
			VK_SAMPLE_COUNT_1_BIT);

		m_DepthTarget = new RenderTarget(instance, depthInfo);

		++i;
		attachmentInfos[i].framebufferAttachment = m_DepthTarget;
		attachmentInfos[i].loadOP = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentInfos[i].storeOP = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentInfos[i].stencilLoadOP = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentInfos[i].stencilStoreOP = VK_ATTACHMENT_STORE_OP_DONT_CARE;

		m_RenderTargets.emplace_back(m_DepthTarget);

		m_VKRenderPass = new RenderPass(instance->getVkLogicalDevice(), attachmentInfos);
		m_FrameBufferHdl = new FrameBuffer(instance->getVkLogicalDevice(), m_VKRenderPass->getRenderPass(), m_RenderTargets);

		return true;
	}
	bool GBufferObject::Resize(std::uint32_t width, std::uint32_t height)
	{
		Destroy();
		m_FrameBufferDimension = Vec2(float(width), float(height));
		return Create();
	}
	void GBufferObject::InitResizeFunctionPointer()
	{
		if (m_Resizeable)
		{
			RecreateFunc = [this](std::uint32_t Width, std::uint32_t Height) -> bool
			{
				return Resize(Width, Height);
			};
		}

		DestroyFunc = [&]() -> void
		{
			Destroy();
		};

		BlendAttachmentGettor = [&](BlendContainer& blendCont, PipelineCreateEntry& createEntry) -> void
		{
			return GetBlendAttachments(blendCont, createEntry);
		};
	}

	void GBufferObject::Destroy()
	{
		if (m_VKRenderPass)
			delete m_VKRenderPass;
		if (m_FrameBufferHdl)
			delete m_FrameBufferHdl;
		if (m_DepthTarget)
			delete m_DepthTarget;
		for (auto& target : m_RenderTargets)
		{
			if (target)
				delete target;
		}
	}

	void GBufferObject::GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry)
	{
	}




}