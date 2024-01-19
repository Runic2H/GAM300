#pragma once
#include "FBOInternal.h"

namespace TDS
{


	class GBufferObject : public FrameBufferObjectInternal<GBufferObject>
	{
	public:
		GBufferObject(Vec2 DimensionInput);

		bool	Create();
		bool	Resize(std::uint32_t width, std::uint32_t height);
		void	InitResizeFunctionPointer();
		void	Destroy();

		void	GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry);
	};

}