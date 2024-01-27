#include "Rendering/Revamped/DeferredController.h"
#include "components/transform.h"
#include "components/GraphicsComponent.h"
#include "GraphicsResource/Revamped/MeshController.h"
#include "AssetManagement/AssetManager.h"
#include "AssetManagement/Revamped/MeshFactory.h"
#include "vulkanTools/VulkanPipeline.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/Renderer.h"
#include "vulkanTools/GlobalBufferPool.h"
#include "Rendering/Revamped/FrameBufferObjects/FBO.h"
#include "Rendering/Revamped/FrameBufferObjects/FBOInternal.h"
#include "Rendering/Revamped/FrameBufferObjects/GBuffer.h"
#include "Rendering/Revamped/FrameBufferObjects/OmniShadowPass.h"
#include "Rendering/Revamped/FrameBufferObjects/LightingPass.h"
namespace TDS
{



	void DeferredController::Init()
	{
		CreatePipelines();


	}
	void DeferredController::CreatePipelines()
	{
		//Create GBuffer pipelines
		{

			GlobalBufferPool::GetInstance()->AddToGlobalPool(sizeof(GlobalUBO), 0, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, "PL");
			PipelineCreateEntry entry{};
			entry.m_NumDescriptorSets = 1;

			entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../assets/shaders/BatchShaderVert.spv"));
			entry.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../assets/shaders/BatchShaderFrag.spv"));
			entry.m_PipelineConfig.m_DstClrBlend = VK_BLEND_FACTOR_ZERO;
			entry.m_PipelineConfig.m_SrcClrBlend = VK_BLEND_FACTOR_ZERO;
			entry.m_PipelineConfig.m_SrcAlphaBlend = VK_BLEND_FACTOR_ZERO;
			entry.m_PipelineConfig.m_DstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			entry.m_PipelineConfig.m_CullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;


			VertexLayout layout =
				VertexLayout(
					{
					  VertexBufferElement(VAR_TYPE::VEC3, "vPosition"),
					  VertexBufferElement(VAR_TYPE::VEC3, "vBiTangent"),
					  VertexBufferElement(VAR_TYPE::VEC3, "vTangent"),
					  VertexBufferElement(VAR_TYPE::VEC3, "vNormals"),
					  VertexBufferElement(VAR_TYPE::VEC2, "vUV"),
					  VertexBufferElement(VAR_TYPE::VEC4, "vColor"),
					  VertexBufferElement(VAR_TYPE::VEC4, "BoneIDs"),
					  VertexBufferElement(VAR_TYPE::VEC4, "Weights"),
					  VertexBufferElement(VAR_TYPE::VEC2, "MeshID"),
					});

			entry.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout, sizeof(TDSModel::Vertex)));

			BufferInfo Buffer{};
			Buffer.m_Data = m_Batch3D.m_BatchBuffers.data();
			Buffer.m_Size = MAX_POSSIBLE_BATCH * sizeof(BatchData);
			Buffer.m_Static = false;
			entry.m_ShaderInputs.m_InputBuffers[15] = Buffer;
			GlobalBufferPool::GetInstance()->AddToGlobalPool(sizeof(GlobalUBO), 5, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, "PL");
			m_DeferredPipelines[DEFERRED_STAGE::STAGE_G_BUFFER_BATCH] = std::make_shared<VulkanPipeline>();
			m_DeferredPipelines[DEFERRED_STAGE::STAGE_G_BUFFER_BATCH]->Create(entry);

			PipelineCreateEntry entry2{};


			entry2.m_NumDescriptorSets = 1;
			entry2.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::VERTEX, "../assets/shaders/InstanceShaderVert.spv"));
			entry2.m_ShaderInputs.m_Shaders.insert(std::make_pair(SHADER_FLAG::FRAGMENT, "../assets/shaders/InstanceShaderFrag.spv"));
			entry2.m_PipelineConfig.m_DstClrBlend = VK_BLEND_FACTOR_ZERO;
			entry2.m_PipelineConfig.m_SrcClrBlend = VK_BLEND_FACTOR_ZERO;
			entry2.m_PipelineConfig.m_SrcAlphaBlend = VK_BLEND_FACTOR_ZERO;
			entry2.m_PipelineConfig.m_DstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			entry2.m_PipelineConfig.m_CullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
			entry2.m_ShaderInputs.m_InputVertex.push_back(VertexBufferInfo(false, layout, sizeof(TDSModel::Vertex)));

			BufferInfo Buffer2{};
			Buffer2.m_Data = m_Instance3D.m_InstanceBuffers.data();
			Buffer2.m_Size = MAX_POSSIBLE_BATCH * sizeof(BatchData);
			Buffer2.m_Static = false;
			entry2.m_ShaderInputs.m_InputBuffers[15] = Buffer2;


			m_DeferredPipelines[DEFERRED_STAGE::STAGE_G_BUFFER_INSTANCE] = std::make_shared<VulkanPipeline>();
			m_DeferredPipelines[DEFERRED_STAGE::STAGE_G_BUFFER_INSTANCE]->Create(entry2);

		}




		//Creating lighting pass
		{




		}








		{




		}
	}
	void DeferredController::G_BufferPass()
	{
		VkCommandBuffer& commandBuffer = GraphicsManager::getInstance().getCommandBuffer();
		auto GBufferPipeline = m_DeferredPipelines[DEFERRED_STAGE::STAGE_G_BUFFER_BATCH];

		GBufferPipeline->SetCommandBuffer(commandBuffer);
		auto frameIndx = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();
		for (auto& meshItr : m_Batch3D.m_BatchUpdateInfo)
		{
			for (auto& updates : meshItr.second.m_MeshUpdates)
			{
				m_Batch3D.m_BatchBuffers[updates.m_MeshID].m_EntityID = updates.m_EntityID;
				m_Batch3D.m_BatchBuffers[updates.m_MeshID].m_isAnimated = updates.m_IsAnimated;
				m_Batch3D.m_BatchBuffers[updates.m_MeshID].m_modelMatrix = updates.m_pTransform->GetFakeTransform();
				m_Batch3D.m_BatchBuffers[updates.m_MeshID].m_TextureID = updates.m_TextureID;
			}
			meshItr.second.m_MeshUpdates.clear();
		}

		GBufferPipeline->UpdateUBO(&globalUBO, sizeof(GlobalUBO), 0, frameIndx);
		GBufferPipeline->UpdateUBO(m_Batch3D.m_BatchBuffers.data(), sizeof(BatchData) * m_Batch3D.m_BatchBuffers.size(), 15, frameIndx);

		if (AssetManager::GetInstance()->GetTextureFactory().m_UpdateArrayBatch)
		{
			GBufferPipeline->UpdateTextureArray(4, VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, AssetManager::GetInstance()->GetTextureFactory().GetTextureArray());
			AssetManager::GetInstance()->GetTextureFactory().m_UpdateArrayBatch = false;
		}

		for (auto& [meshName, meshUpdate] : m_Batch3D.m_BatchUpdateInfo)
		{
			GBufferPipeline->BindPipeline();
			GBufferPipeline->BindVertexBuffer(*meshUpdate.m_MeshBuffer->m_VertexBuffer);
			GBufferPipeline->BindIndexBuffer(*meshUpdate.m_MeshBuffer->m_IndexBuffer);
			GBufferPipeline->BindDescriptor(frameIndx, 1);
			GBufferPipeline->BindArrayDescriptorSet(0, 1, 1);

			GBufferPipeline->DrawIndexed(*meshUpdate.m_MeshBuffer->m_VertexBuffer, *meshUpdate.m_MeshBuffer->m_IndexBuffer, frameIndx);
		}
		m_Batch3D.m_BatchUpdateInfo.clear();

	}
	void DeferredController::G_BufferInstanced()
	{
		auto GBufferPipeline = m_DeferredPipelines[DEFERRED_STAGE::STAGE_G_BUFFER_INSTANCE];
		int startingOffset = 0;
		for (auto& itr : m_Instance3D.m_instanceRenderManager.m_InstanceUpdateInfo)
		{
			auto& instanceReq = m_Instance3D.m_InstanceRequests[m_Instance3D.m_GroupIdx];
			instanceReq.m_MeshBuffer = itr.first;

			for (std::uint32_t i = 0; i < itr.second.m_Index; ++i)
			{
				auto& meshUpdateData = itr.second.m_Updates[i];

				auto& InstanceInfo = instanceReq.m_RenderInstanceInfo;
				auto& instaneBuffer = m_Instance3D.m_InstanceBuffers[m_Instance3D.m_TotalInstances];

				InstanceInfo.m_InstanceOffset = startingOffset;
				InstanceInfo.m_Instances = itr.second.m_Index;

				{
					instaneBuffer.m_MaterialID = m_Instance3D.m_TotalInstances;
					instaneBuffer.m_isAnimated = meshUpdateData.m_IsAnimated;
					instaneBuffer.m_TextureID = meshUpdateData.m_TextureID;
					instaneBuffer.m_EntityID = meshUpdateData.m_EntityID;
					instaneBuffer.m_modelMatrix = meshUpdateData.m_pTransform->GetTransformMatrix();
				}

				++m_Instance3D.m_TotalInstances;

			}
			startingOffset = m_Instance3D.m_TotalInstances;
			itr.second.m_Index = 0;
			++m_Instance3D.m_GroupIdx;
		}

		auto frameIndx = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();

		GBufferPipeline->UpdateUBO(&globalUBO, sizeof(GlobalUBO), 0, frameIndx);
		GBufferPipeline->UpdateUBO(m_Instance3D.m_InstanceBuffers.data(), sizeof(BatchData) * m_Instance3D.m_TotalInstances, 15, frameIndx);

		if (AssetManager::GetInstance()->GetTextureFactory().m_UpdateArrayInstance)
		{
			GBufferPipeline->UpdateTextureArray(4, VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, AssetManager::GetInstance()->GetTextureFactory().GetTextureArray());
			AssetManager::GetInstance()->GetTextureFactory().m_UpdateArrayInstance = false;
		}

		VkCommandBuffer& commandBuffer = GraphicsManager::getInstance().getCommandBuffer();

		GBufferPipeline->SetCommandBuffer(commandBuffer);
		for (std::uint32_t i = 0; i < m_Instance3D.m_GroupIdx; ++i)
		{
			auto& instanceReq = m_Instance3D.m_InstanceRequests[i];

			GBufferPipeline->BindPipeline();
			GBufferPipeline->BindVertexBuffer(*instanceReq.m_MeshBuffer->m_VertexBuffer);
			GBufferPipeline->BindIndexBuffer(*instanceReq.m_MeshBuffer->m_IndexBuffer);
			GBufferPipeline->BindDescriptor(frameIndx, 1);
			GBufferPipeline->BindArrayDescriptorSet(0, 1, 1);
			GBufferPipeline->SubmitPushConstant(&instanceReq.m_RenderInstanceInfo.m_InstanceOffset, sizeof(std::uint32_t), SHADER_FLAG::VERTEX);
			GBufferPipeline->DrawInstancedIndexed(*instanceReq.m_MeshBuffer->m_VertexBuffer, *instanceReq.m_MeshBuffer->m_IndexBuffer, instanceReq.m_RenderInstanceInfo.m_Instances, frameIndx);

			instanceReq.m_RenderInstanceInfo.m_InstanceOffset = 0;
			instanceReq.m_RenderInstanceInfo.m_Instances = 0;
		}

		m_Instance3D.m_TotalInstances = 0;
		m_Instance3D.m_GroupIdx = 0;

	}
	void DeferredController::ClearBatchSubmission()
	{
		m_Instance3D.m_GroupIdx = 0;
		m_Instance3D.m_TotalInstances = 0;

	}
	void DeferredController::SubmitMesh(std::uint32_t entityID, GraphicsComponent* graphComp, Transform* transformComp)
	{
		Mat4 temp{};


			if (transformComp->GetPosition() == transformComp->GetFakePosition() &&
				transformComp->GetScale() == transformComp->GetFakeScale()
				&& transformComp->GetRotation() == transformComp->GetFakeRotation())
			{
				temp = transformComp->GetTransformMatrix();
			}
			else
			{

				temp = transformComp->GetFakeTransform();
			}
		

		std::string texName = graphComp->m_TextureName;

		MeshController* pModelController = graphComp->m_MeshControllerRef.m_ResourcePtr;


		if (graphComp->m_ModelName != graphComp->m_MeshControllerRef.m_AssetName)
		{
			AssetManager::GetInstance()->GetMeshFactory().UnloadReference(graphComp->m_MeshControllerRef);
			MeshController* temp = AssetManager::GetInstance()->GetMeshFactory().GetMeshController(graphComp->m_ModelName, graphComp->m_MeshControllerRef);
			if (temp == nullptr)
				temp = graphComp->m_MeshControllerRef.m_ResourcePtr;

			else
			{
				graphComp->m_MeshControllerRef.m_AssetName = graphComp->m_ModelName;
				graphComp->m_MeshControllerRef.m_ResourcePtr = temp;
				pModelController = temp;
			}
			pModelController = temp;
		}

		//Check if this graphics component is even referencing a model
		if (pModelController == nullptr) return;


		int textureID = AssetManager::GetInstance()->GetTextureFactory().GetTextureIndex(graphComp->m_TextureName, graphComp->m_TextureReference);

		if (textureID == -1)
			textureID = 499;


		if (pModelController->m_Instancing == false)
		{
			SubmitBatch(entityID, textureID, transformComp, graphComp);
		}
		else
		{
			SubmitInstance(entityID, textureID, transformComp, graphComp);
		}


	}
	void DeferredController::SubmitBatch(std::uint32_t entityID, int TextureID, Transform* transformComp, GraphicsComponent* graphComp)
	{
		MeshController* pMeshController = graphComp->m_MeshControllerRef.m_ResourcePtr;
		MeshBuffer* meshBuffer = pMeshController->GetMeshBuffer();

		//Check if batch VBO and EBO exist
		if (meshBuffer == nullptr) return;


		//Check if model is referencing a mesh
		int meshID = pMeshController->GetMeshID(graphComp->m_MeshName);

		if (meshID == -1) return;

		m_Batch3D.m_BatchUpdateInfo[graphComp->m_ModelName].m_MeshBuffer = pMeshController->GetMeshBuffer();
		auto& batchUpdate = m_Batch3D.m_BatchUpdateInfo[graphComp->m_ModelName].m_MeshUpdates.emplace_back();

		batchUpdate.m_EntityID = entityID;
		batchUpdate.m_pTransform = transformComp;
		batchUpdate.m_TextureID = TextureID;
		batchUpdate.m_IsAnimated = false;
		batchUpdate.m_MeshID = meshID;
		batchUpdate.m_ShowMesh = graphComp->ShowMesh();
	}
	void DeferredController::SubmitInstance(std::uint32_t entityID, int TextureID, Transform* transformComp, GraphicsComponent* graphComp)
	{
		MeshController* pMeshController = graphComp->m_MeshControllerRef.m_ResourcePtr;
		MeshBuffer* meshBuffer = pMeshController->GetMeshBuffer();

		if (m_Instance3D.m_GroupIdx >= MAX_INSTANCE_BUFFER)
		{
			TDS_ERROR("We have reached the maximum amount of instances!");
			return;
		}

		auto& instanceUpdatePack = m_Instance3D.m_instanceRenderManager.m_InstanceUpdateInfo[meshBuffer];


		MeshUpdate* updateData = (instanceUpdatePack.m_Index == instanceUpdatePack.m_Updates.size()) ?
			&instanceUpdatePack.m_Updates.emplace_back() : &instanceUpdatePack.m_Updates[instanceUpdatePack.m_Index];


		updateData->m_pTransform = transformComp;
		updateData->m_IsAnimated = false;
		updateData->m_TextureID = TextureID;
		updateData->m_EntityID = entityID;
		updateData->m_MeshID = 0;
		updateData->m_ShowMesh = graphComp->ShowMesh();
		++instanceUpdatePack.m_Index;

	}
	std::shared_ptr<VulkanPipeline> DeferredController::GetDeferredPipeline(DEFERRED_STAGE stage)
	{
		return m_DeferredPipelines[stage];
	}
	void DeferredController::ShutDown()
	{
		for (auto& pipelines : m_DeferredPipelines)
		{
			if (pipelines != nullptr)
			{
				pipelines->ShutDown();
			}
		}
	}
	void DeferredController::CreateFrameBuffers(std::uint32_t width, std::uint32_t height)
	{



	}
	void DeferredController::Resize(std::uint32_t width, std::uint32_t height)
	{
	}

}