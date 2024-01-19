#pragma once
#include "vulkanTools/VulkanHelper.h"
#include "Rendering/RenderTarget.h"
#include "Rendering/renderPass.h"
#include "vulkanTools/FrameBuffer.h"
namespace TDS
{
	enum class FBO_TYPE
	{
		G_BUFFER = 0,
		POINT_LIGHT,
		SPOT_LIGHT,
		SHADOW,
		OMNI_SHADOW
	};

	struct FrameBufferObjectCreateInfo
	{
		bool					m_Resizeable;
		bool					m_AutoSync;
		bool					m_TargetSwapchain;
		Vec2					m_FrameBufferDimension;
		VkSampleCountFlagBits	m_SampleCnt;
	};

	struct PipelineCreateEntry;

	class FrameBufferObject
	{
	protected:
		using BlendContainer = std::vector<VkPipelineColorBlendAttachmentState>;

		bool												m_Resizeable = true;
		bool												m_AutoSync = true;
		bool												m_TargetSwapchain = false;
		Vec2												m_FrameBufferDimension = { 0.f,0.f };
		VkSampleCountFlagBits								m_SampleCnt = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		FrameBuffer*										m_FrameBufferHdl = nullptr;
		RenderPass*											m_VKRenderPass = nullptr;
		RenderTarget*										m_DepthTarget = nullptr;

		std::function<bool(std::uint32_t, std::uint32_t)>	RecreateFunc = nullptr;
		std::function<void()>								DestroyFunc = nullptr;


		std::vector<RenderTarget*>							m_RenderTargets{};
		std::vector<RenderTargetCI>							m_RenderAttachmentInfo{};

	public:
		std::function<void(BlendContainer&, PipelineCreateEntry&)>	BlendAttachmentGettor = nullptr;


		FBO_TYPE											m_FBOType = FBO_TYPE::G_BUFFER;

		FrameBufferObject() = default;
		~FrameBufferObject() = default;

		void					BeginRenderPass(VkCommandBuffer commandBuffer);
		void					EndRenderPass(VkCommandBuffer commandBuffer);
		bool					Resize(std::uint32_t width, std::uint32_t height);
		void					SetClearColour(const Vec4& color);
		void					Destroy();
		VkSampleCountFlagBits	QueryMaxSamplingCnt();

		CREATE_SETTOR(Resizeable, bool);
		CREATE_SETTOR(AutoSync, bool);
		CREATE_SETTOR(TargetSwapchain, bool);
		CREATE_SETTOR(SampleCnt, VkSampleCountFlagBits);

		CREATE_NON_REF_GETTOR(Resizeable, bool);
		CREATE_NON_REF_GETTOR(AutoSync, bool);
		CREATE_NON_REF_GETTOR(TargetSwapchain, bool);
		CREATE_NON_REF_GETTOR(FrameBufferDimension, Vec2);
		CREATE_NON_REF_GETTOR(SampleCnt, VkSampleCountFlagBits);
		CREATE_NON_REF_GETTOR(DepthTarget, RenderTarget*);

		CREATE_GETTOR(RenderTargets, std::vector<RenderTarget*>);
		CREATE_GETTOR(RenderAttachmentInfo, std::vector<RenderTargetCI>);
		CREATE_GETTOR(FrameBufferHdl, FrameBuffer*);
		CREATE_GETTOR(VKRenderPass, RenderPass*);

	};






}