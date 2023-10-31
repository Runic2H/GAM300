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
#include "FrameInfo.h"
#include "TDSMath.h"
#include "components/GraphicsComponent.h"
#include "components/transform.h"
#include "dotnet/ImportExport.h"
#include "vulkanTools/VulkanPipeline.h"


#include <memory>

namespace TDS {
	class VulkanPipeline;
	class PointLightSystem {
	public:
		//Constructor and destructor
		DLL_API PointLightSystem(VulkanInstance& Instance);
		DLL_API ~PointLightSystem();

		//no copy constructor
		DLL_API PointLightSystem(const PointLightSystem&) = delete;
		DLL_API PointLightSystem& operator=(const PointLightSystem&) = delete;
		
		//update system with the position of the active point lights 
		DLL_API void update(GlobalUBO& UBO, GraphicsComponent* Gp, Transform* Trans);
		//render the active point lights
		DLL_API void render(GraphicsComponent* Gp, Transform* Trans);

		DLL_API VulkanPipeline& GetPipeline();
	private:

		VulkanInstance&					m_Instance;

		std::unique_ptr<VulkanPipeline>			m_Pipeline;
		//std::unique_ptr<Pipeline>				m_Pipeline;
		//VkPipelineLayout						m_pipelineLayout;
		int										m_pointlightcount;
		std::array<bool, Max_Lights>			m_vPointLightBoolMap{ false };
	};


}
#endif // !TDS_POINT_LIGHT_SYSTEM