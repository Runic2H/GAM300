#include "Rendering/RendererSystem.h"
#include "components/components.h"
#include "Rendering/RenderDataManager.h"
#include "Rendering/Renderer3D.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/VulkanPipeline.h"
#include "vulkanTools/vulkanSwapChain.h"
#include "vulkanTools/Renderer.h"
#include "Rendering/renderPass.h"
#include "vulkanTools/FrameBuffer.h"
namespace TDS
{
	struct PushConstantData {
		Mat4 ModelMat{ 1.f };
		Mat4 NormalMat{ 1.f };
	};
	float RendererSystem::lightPosX = 0.f;
	void RendererSystem::OnInit()
	{

	}
	void RendererSystem::OnUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _TransformComponent, GraphicsComponent* _Graphics)
	{
		std::uint32_t frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();

		VkCommandBuffer commandBuffer = GraphicsManager::getInstance().getCommandBuffer();

		for (size_t i = 0; i < entities.size(); ++i)
		{
			Renderer3D::getPipeline()->SetCommandBuffer(commandBuffer);
			GraphicsManager::getInstance().m_PointLightRenderer->GetPipeline().SetCommandBuffer(commandBuffer);
			_Graphics[i].GetAsset().m_GUID = *assetManager->GetModelFactory().m_LoadedModelsGUID.begin();
			_Graphics[i].GetAsset().m_Identifier.CreateTypeIDByName(assetManager->GetModelFactory().m_ModelMap.begin()->first);
			_Graphics[i].GetAsset().m_Identifier.GetTypeName<AssetModel>();

			assetManager->getResourceManager().getResource(_Graphics[i].GetAsset());

			if (_Graphics[i].ShowMesh() == true)
			{
				if (Renderer3D::getPipeline()->GetCreateEntry().m_EnableDoubleBuffering)
				{

					GlobalUBO& ubo = RendererDataManager::GetUBO(_Graphics->GetAsset().m_GUID.GetUniqueID());
					ModelElement elem = RendererDataManager::GetModelElement(_Graphics->GetAsset().m_GUID.GetUniqueID(), _Graphics->GetAsset().m_Reference);
					PushConstantData pushData{};

					if (Vec3 Scale = _TransformComponent[i].GetScale(); Scale.x <= 0.f || Scale.y <= 0.f || Scale.z <= 0.f) {
					}
					else {
						_TransformComponent[i].GenerateTransfom();
					}
					Mat4 temp = _TransformComponent[i].GetTransformMatrix();
					pushData.ModelMat = temp;
					temp.transpose();
					temp.inverse();
					pushData.NormalMat = temp;

					ubo.m_View = GraphicsManager::getInstance().GetCamera().GetViewMatrix();
					GraphicsManager::getInstance().m_PointLightRenderer->update(ubo, &_Graphics[i], &_TransformComponent[i]);
					ubo.m_Projection = Mat4::Perspective(GraphicsManager::getInstance().GetCamera().m_Fov * Mathf::Deg2Rad,
						GraphicsManager::getInstance().GetSwapchainRenderer().getAspectRatio(), 0.1f, 10.f);
					ubo.m_Projection.m[1][1] *= -1;

					if (_Graphics[i].IsPointLight()) { //if point light, use the use lights pipeline to render
						//GraphicsManager::getInstance().m_PointLightRenderer->GetPipeline().BindPipeline();
						GraphicsManager::getInstance().m_PointLightRenderer->GetPipeline().BindDescriptor(frame);
						//TDS_INFO("number of lights {}", ubo.m_activelights);
						GraphicsManager::getInstance().m_PointLightRenderer->GetPipeline().UpdateUBO(&ubo, sizeof(GlobalUBO), 1, frame);
						GraphicsManager::getInstance().m_PointLightRenderer->render(&_Graphics[i], &_TransformComponent[i]);
					}
					else {//if not point light render using model
						Renderer3D::getPipeline()->BindPipeline();
						Renderer3D::getPipeline()->BindDescriptor(frame);
						Renderer3D::getPipeline()->UpdateUBO(&ubo, sizeof(GlobalUBO), 0, frame);
						Renderer3D::getPipeline()->SubmitPushConstant(&pushData, sizeof(PushConstantData), SHADER_FLAG::VERTEX);

						Renderer3D::getPipeline()->BindVertexBuffer(*elem.m_VertexBuffer);
						Renderer3D::getPipeline()->BindIndexBuffer(*elem.m_IndexBuffer);
						Renderer3D::getPipeline()->DrawIndexed(*elem.m_VertexBuffer, *elem.m_IndexBuffer, frame);
					}
					/*Renderer3D::getPipeline()->BindPipeline();
					Renderer3D::getPipeline()->UpdateUBO(&ubo, sizeof(GlobalUBO), 0, frame);
					Renderer3D::getPipeline()->BindDescriptor(frame);
					Renderer3D::getPipeline()->SubmitPushConstant(&pushData, sizeof(PushConstantData), SHADER_FLAG::VERTEX);
				
					Renderer3D::getPipeline()->BindVertexBuffer(*elem.m_VertexBuffer);
					Renderer3D::getPipeline()->BindIndexBuffer(*elem.m_IndexBuffer);
					Renderer3D::getPipeline()->DrawIndexed(*elem.m_VertexBuffer, *elem.m_IndexBuffer, frame);
					*/
				}


			}
		}
		//GraphicsManager::getInstance().GetSwapchainRenderer().EndSwapChainRenderPass(commandBuffer);


	/*	OnRender(entities, &_transform, _Graphics)*/
		/*SubmitModels(entities, &_transform, _Graphics);*/
	/*	Renderer3D::DrawFrame(*RendererDataManager::GetInstance());*/
	}
	void RendererSystem::OnRender(const float dt, const std::vector<EntityID>& entities, GraphicsComponent* _Graphics)
	{
	}
	void RendererSystem::SubmitPointLights()
	{
	}
	void RendererSystem::SubmitModels(const std::vector<EntityID>& entities, Transform* _transform, GraphicsComponent* _Graphics)
	{


	}
	void RendererSystem::SubmitTextures()
	{
	}
}