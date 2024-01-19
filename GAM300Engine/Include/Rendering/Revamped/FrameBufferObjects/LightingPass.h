#pragma once
#include "FBOInternal.h"

namespace TDS
{

	class PointLightPass : public FrameBufferObjectInternal<PointLightPass>
	{
	public:
		PointLightPass(Vec2 DimensionInput);
		bool	Create();
		bool	Resize(std::uint32_t width, std::uint32_t height);
		void	InitResizeFunctionPointer();
		void	Destroy();

		void	GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry);
	};


	class SpotLightPass : public FrameBufferObjectInternal<SpotLightPass>
	{
	public:
		SpotLightPass(Vec2 DimensionInput);
		bool	Create();
		bool	Resize(std::uint32_t width, std::uint32_t height);
		void	InitResizeFunctionPointer();
		void	Destroy();


		void	GetBlendAttachments(BlendContainer& blendCont, PipelineCreateEntry& createEntry);
	};

}