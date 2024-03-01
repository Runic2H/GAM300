#pragma once
#include "GraphicsResource/MaterialInfo.h"
#include "ResourceManagement/ResourceRef.h"
#include "GraphicsResource/TextureInfo.h"
namespace TDS
{

	enum class MATERIAL_TYPE
	{
		PHONG_BLING = 0,
		PBR_RENDERER
	};

	class VulkanPipeline;

	class MaterialBase
	{
	public:
		MaterialBase() = default;
		virtual ~MaterialBase() = default;

		virtual void						BuildMaterialPipeline() = 0;
		void								Destroy();
		std::shared_ptr<VulkanPipeline>		GetMaterialPipeline();
	protected:
		std::string							m_MaterialRendererName;
		std::shared_ptr<VulkanPipeline>		m_Pipeline;
		MaterialMapList						m_MaterialList;
	};


}