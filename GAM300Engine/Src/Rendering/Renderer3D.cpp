#include "Rendering/Renderer3D.h"
#include "vulkanTools/DirectFrameBuffer.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/VulkanPipeline.h"
#include "Rendering/RenderDataManager.h"
#include "ResourceManagement/ResourceRef.h"
#include "vulkanTools/vulkanSwapChain.h"
#include "GraphicsResource/VertexInfo.h"
#include "vulkanTools/GlobalBufferPool.h"
#include "vulkanTools/Model.h"
#include "vulkanTools/FrameInfo.h"
#include "GraphicsResource/GeomStruct.h"
namespace TDS
{
	std::shared_ptr<Renderer3D> Renderer3D::getInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = std::make_shared<Renderer3D>();
		return m_Instance;
	}
	void Renderer3D::Init()
	{
		Renderer3D& inst = *getInstance();
		PipelineCreateEntry entry{};
		entry.m_NumDescriptorSets = 1;
		
		entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../assets/shaders/shadervert.spv"));
		entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../assets/shaders/shaderfrag.spv"));
		entry.m_PipelineConfig.m_DstClrBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_SrcClrBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_SrcAlphaBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_DstAlphaBlend = VK_BLEND_FACTOR_ZERO;
		entry.m_PipelineConfig.m_CullMode= VkCullModeFlagBits::VK_CULL_MODE_NONE;
		VertexLayout layout = 
		VertexLayout(
		{ 
		  VertexBufferElement(VAR_TYPE::VEC3, "vPosition"),
		  VertexBufferElement(VAR_TYPE::VEC3, "vColor"),
		  VertexBufferElement(VAR_TYPE::VEC3, "inTexCoord"),
		  VertexBufferElement(VAR_TYPE::VEC4, "vNormals"),
		});
		GlobalBufferPool::GetInstance()->AddToGlobalPool(sizeof(GlobalUBO), 0, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, "PL");
		entry.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout, sizeof(VertexData)));
		inst.m_DefaultPipeline = std::make_shared<VulkanPipeline>();
		

		inst.m_DefaultPipeline->Create(entry);
	
		inst.m_TempPipeline = std::make_shared<VulkanPipeline>();

		VertexLayout layout2 =
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

		PipelineCreateEntry entry2{};
		entry2.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../assets/shaders/TempShaderVert.spv"));
		entry2.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../assets/shaders/TempShaderFrag.spv"));
		entry2.m_PipelineConfig.m_DstClrBlend = VK_BLEND_FACTOR_ZERO;
		entry2.m_PipelineConfig.m_SrcClrBlend = VK_BLEND_FACTOR_ZERO;
		entry2.m_PipelineConfig.m_SrcAlphaBlend = VK_BLEND_FACTOR_ZERO;
		entry2.m_PipelineConfig.m_DstAlphaBlend = VK_BLEND_FACTOR_ZERO;
		entry2.m_PipelineConfig.m_CullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
		entry2.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout2, sizeof(TDSModel::Vertex)));

		inst.m_TempPipeline->Create(entry2);
	}
	std::shared_ptr<VulkanPipeline>& Renderer3D::getPipeline()
	{
		return m_Instance->m_DefaultPipeline;
	}

	std::shared_ptr<VulkanPipeline>& Renderer3D::getTempPipeline()
	{
		return m_Instance->m_TempPipeline;
	}

	void Renderer3D::ShutDown()
	{
		m_DefaultPipeline->ShutDown();
	}
}