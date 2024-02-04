#include "Rendering/Revamped/MaterialPipeline.h"
#include "vulkanTools/VulkanPipeline.h"
#include "GraphicsResource/GeomStruct.h"
namespace TDS
{
	void MaterialBase::Destroy()
	{
		m_Pipeline->ShutDown();
	}
	std::shared_ptr<VulkanPipeline> MaterialBase::GetMaterialPipeline()
	{
		return m_Pipeline;
	}

}