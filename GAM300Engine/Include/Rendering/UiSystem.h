#pragma once
#include "ecs/ecs.h"
#include "camera/SphereFrustum.h"

namespace TDS
{
	class Transform;
	class UISprite;




	class DLL_API UiSystem
	{
		public:
			static void Init();
			static void Update(const float dt, const std::vector<EntityID>& entities, Transform* transform, UISprite* _Sprite);
			static void ToggleEnableLayer(int layerID, bool condition = true);
			static void UpdateAABB(UISprite* _Sprite, Transform* _trans);
			static void UpdatePropertiesFromParent(EntityID curr, UISprite* _CurrentTransform);
			static std::unordered_map<int, bool> m_Layers;
	};

}