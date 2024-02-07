#pragma once
#include "MathCommon.h"
#include "dotnet/ImportExport.h"
namespace TDS
{

	class Model;
	class RendererDataManager;
	class VulkanPipeline;
	class FrameBuffer;
	class DLL_API Renderer3D
	{
	private:
		inline static std::shared_ptr<Renderer3D> m_Instance = nullptr;
		std::shared_ptr<VulkanPipeline> m_DefaultPipeline = nullptr;
		std::shared_ptr<VulkanPipeline> m_TempPipeline = nullptr;

	public:
		static std::shared_ptr<Renderer3D> getInstance();
		static void Init();
		static std::shared_ptr<VulkanPipeline>& getPipeline();
		static std::shared_ptr<VulkanPipeline>& getTempPipeline();
		void ShutDown();



	};
}