#pragma once
#include "FBO.h"

namespace TDS
{
	template <typename DERIVED>
	class FrameBufferObjectInternal : public FrameBufferObject
	{
	private:

	public:

		FrameBufferObjectInternal()
		{
			DERIVED(Vec2(1.f, 1.f));
			m_Resizeable = true;
			m_AutoSync = true; 
			m_TargetSwapchain = false;
			m_FrameBufferDimension = Vec2(1.f, 1.f);
			m_SampleCnt = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
			m_FrameBufferHdl = nullptr;
			m_VKRenderPass = nullptr;
			InitResizeFunctionPointer();
		}


		FrameBufferObjectInternal(FrameBufferObjectCreateInfo& createInfo)
		{
			DERIVED(createInfo.m_FrameBufferDimension);
			m_Resizeable = createInfo.m_Resizeable;
			m_AutoSync = createInfo.m_AutoSync;
			m_TargetSwapchain = createInfo.m_TargetSwapchain;
			m_FrameBufferDimension = createInfo.m_FrameBufferDimension;
			m_SampleCnt = createInfo.m_SampleCnt;
			m_FrameBufferHdl = nullptr;
			m_VKRenderPass = nullptr;
			
			InitResizeFunctionPointer();
		}

		~FrameBufferObjectInternal()
		{
			Destroy();
		}

		bool	Create()
		{
			return static_cast<DERIVED*>(this)->Create();
		}

		bool	Resize(std::uint32_t width, std::uint32_t height)
		{
			return static_cast<DERIVED*>(this)->Resize(width, height);
		}
		void	InitResizeFunctionPointer()
		{
			static_cast<DERIVED*>(this)->InitResizeFunctionPointer();
		}
	};
}