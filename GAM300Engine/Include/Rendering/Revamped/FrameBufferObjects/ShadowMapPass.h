#pragma once
#include "FBOInternal.h"

namespace TDS
{


	class ShadowMapPass : public FrameBufferObjectInternal<ShadowMapPass>
	{
	private:
		RenderTargetCI						m_ShadowDepth;
	public:
		ShadowMapPass(Vec2 DimensionInput);

		bool	Create();
		bool	Resize(std::uint32_t width, std::uint32_t height);
		void	InitResizeFunctionPointer();
		void	Destroy();


		void	GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry);

	};




}