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
	PBRMaterial::PBRMaterial()
	{
	}
	PBRMaterial::~PBRMaterial()
	{
	}
	void PBRMaterial::BuildMaterialPipeline()
	{
		m_Pipeline = std::make_shared<VulkanPipeline>();
		PipelineCreateEntry entry{};
		entry.m_NumDescriptorSets = 1;

		entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../assets/shaders/shadervert.spv"));
		entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../assets/shaders/shaderfrag.spv"));
		entry.m_PipelineConfig.m_DstClrBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_SrcClrBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_SrcAlphaBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_DstAlphaBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_CullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
		VertexLayout layout =
			VertexLayout(
				{
				  VertexBufferElement(VAR_TYPE::VEC3, "vPosition"),
				  VertexBufferElement(VAR_TYPE::VEC3, "vBitangent"),
				  VertexBufferElement(VAR_TYPE::VEC3, "vTangent"),
				  VertexBufferElement(VAR_TYPE::VEC3, "vNormals"),
				  VertexBufferElement(VAR_TYPE::VEC2, "vUV"),
				  VertexBufferElement(VAR_TYPE::VEC4, "vColor"),
				  VertexBufferElement(VAR_TYPE::VEC4, "BoneIDs"),
				  VertexBufferElement(VAR_TYPE::VEC4, "Weights"),
				});

		entry.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout, sizeof(TDSModel::Vertex)));

		m_Pipeline->Create(entry);
	}
}