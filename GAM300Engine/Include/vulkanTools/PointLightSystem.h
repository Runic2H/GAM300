/*!*************************************************************************
****
\file PointLightSystem.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the PointLightSystem Class and its member functions
****************************************************************************
***/
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
		//Constructor and destructor
		PointLightSystem(VulkanInstance& Instance, VkRenderPass renderpass, VkDescriptorSetLayout globalSetLayout);
		~PointLightSystem();

		//no copy constructor
		PointLightSystem(const PointLightSystem&) = delete;
		PointLightSystem& operator=(const PointLightSystem&) = delete;
		
		//update system with the position of the active point lights 
		void update(FrameInfo& frameInfo, GlobalUBO& UBO);
		//render the active point lights
		void render(FrameInfo& frameInfo);
	private:
		//create pipeline layout for pointlights
		void createPipelineLayout(VkDescriptorSetLayout globalsetlayout);
		//create a graphic pipeline for point lights
		void createPipeline(VkRenderPass renderpass);

		VulkanInstance&					m_Instance;

		std::unique_ptr<Pipeline>		m_Pipeline;
		VkPipelineLayout				m_pipelineLayout;
	};


}
#endif // !TDS_POINT_LIGHT_SYSTEM