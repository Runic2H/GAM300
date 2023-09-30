#ifndef TDS_POINT_LIGHT_SYSTEM
#define TDS_POINT_LIGHT_SYSTEM

#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/Pipeline.h"
#include "FrameInfo.h"
#include "TDSMath.h"
#include "dotnet/ImportExport.h"


#include <memory>

namespace TDS {
	class DLL_API PointLightSystem {
	public:
		PointLightSystem(VulkanInstance& Instance, VkRenderPass renderpass, VkDescriptorSetLayout globalSetLayout);
		~PointLightSystem();

		PointLightSystem(const PointLightSystem&) = delete;
		PointLightSystem& operator=(const PointLightSystem&) = delete;

		void update(FrameInfo& frameInfo, GlobalUBO& UBO);
		void render(FrameInfo& frameInfo);
	private:
		void createPipelineLayout(VkDescriptorSetLayout globalsetlayout);
		void createPipeline(VkRenderPass renderpass);

		VulkanInstance& m_Instance;

		std::unique_ptr<Pipeline> m_Pipeline;
		VkPipelineLayout m_pipelineLayout;
	};


}
#endif // !TDS_POINT_LIGHT_SYSTEM