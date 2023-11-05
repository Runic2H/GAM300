#include "Rendering/DebugRenderer.h"
#include "GraphicsResource/AssetModel.h"
namespace TDS {
	struct DebugPushConstants {
		Mat4 TransformMatrix;
		Vec4 DebugColor;
	};
	DebugRenderer::DebugRenderer(VulkanInstance& Instance) : m_Instance(Instance) {
		PipelineCreateEntry PipelineEntry;
		PipelineEntry.m_NumDescriptorSets = 1;
		PipelineEntry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../assets/shaders/DebugVert.spv"));
		PipelineEntry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../assets/shaders/DebugFrag.spv"));
		PipelineEntry.m_PipelineConfig.m_EnableDepthTest = true;
		PipelineEntry.m_PipelineConfig.m_EnableDepthWrite = true;
		PipelineEntry.m_PipelineConfig.m_PipelineDrawModes = { VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_LIST };
		VertexLayout layout = VertexLayout(
			{
			  VertexBufferElement(VAR_TYPE::VEC3, "vPosition"),
			  VertexBufferElement(VAR_TYPE::VEC3, "vColor"),
			});
		PipelineEntry.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout, sizeof(VertexData)));
		m_Pipeline = std::make_unique <VulkanPipeline>();
		m_Pipeline->Create(PipelineEntry);
	}

	DebugRenderer::~DebugRenderer() {}

	void DebugRenderer::Render(GraphicsComponent* Gp, Transform* Transform) {
		m_Pipeline->BindPipeline(VK_PRIMITIVE_TOPOLOGY_LINE_LIST);
		DebugPushConstants Pushdata;
		Pushdata.TransformMatrix = Transform->GetOffsetMatrix();
		Pushdata.DebugColor = { 0.f,1.f,0.f,1.f };
		m_Pipeline->SubmitPushConstant(&Pushdata, sizeof(DebugPushConstants), SHADER_FLAG::VERTEX | SHADER_FLAG::FRAGMENT);
		
		m_Pipeline->BindVertexBuffer(*Gp->GetAsset().m_ResourcePtr->GetVertexBuffer());
		m_Pipeline->BindIndexBuffer(*Gp->GetAsset().m_ResourcePtr->GetIndexBuffer());
	}
	VulkanPipeline& DebugRenderer::GetPipeline() {
		return *m_Pipeline;
	}
}