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

			//This functionalities arent supposed to be here, will move it in the future
			static void UpdatePropertiesFromParent(EntityID curr);
			static bool IsDirectChildOfMainParent(EntityID entity);
			static void UpdateDescendantsActiveness(EntityID parent, bool isActive);

			static std::unordered_map<int, bool> m_Layers;
	};

}