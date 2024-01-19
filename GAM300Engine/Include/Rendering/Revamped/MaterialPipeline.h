#pragma once
#include "GraphicsResource/MaterialInfo.h"
#include "ResourceManagement/ResourceRef.h"
#include "GraphicsResource/TextureInfo.h"
namespace TDS
{

	enum class MATERIAL_PIPELINE
	{
		PBR_RENDERER = 0
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




	class PBRMaterial : public MaterialBase
	{
	private:
		struct PBRinfo
		{
			Vec4			m_Albedo;

			float			m_Metalness = 0.2f;
			float			m_Roughness = 1.f;
			float			m_Emissive = 1.f;
			int				m_UseMaterialTexture;

			std::uint32_t	m_AlbedoTexID;
			std::uint32_t	m_MetallicTexID;
			std::uint32_t	m_RoughnessTexID;
			std::uint32_t	m_AOTexID;

			Vec4			m_NormalMetallicID; // x = normal, y = metallic

		};

	public:
		PBRMaterial();
		virtual ~PBRMaterial();
		virtual void						BuildMaterialPipeline();




	};

}