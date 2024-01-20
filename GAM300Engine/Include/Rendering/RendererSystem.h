#pragma once
#include "ecs/ecs.h"
#include "AssetManagement/AssetManager.h"
#include "vulkanTools/Descriptor.h"
#include "vulkanTools/RendererManager.h"
namespace TDS
{
	class Transform;
	class Model;
	class GraphicsComponent;

	class RendererSystem
	{
	public:
		static void		OnInit();
		static void		OnUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _Component, GraphicsComponent* _Graphics);
		static void		OnRenderDeferred(const float dt, const std::vector<EntityID>& entities, Transform* _Component, GraphicsComponent* _Graphics);


		static void		OnRender(const float dt, const std::vector<EntityID>& entities, Transform* _Component, GraphicsComponent* _Graphics);
		static void		onRenderTempFixed(const float dt, const std::vector<EntityID>& entities, Transform* _Component, GraphicsComponent* _Graphics);
		static void		RenderPointLight(Transform* _Component, GraphicsComponent* _Graphics);


		static void		UpdateGraphicsData(GraphicsComponent* _Graphics);
		static void		UpdateTexture(GraphicsComponent* _Graphics);


		DLL_API static float lightPosX;

	};
}