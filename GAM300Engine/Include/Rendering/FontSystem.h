#pragma once
#include "ecs/ecs.h"
#include "camera/SphereFrustum.h"
namespace TDS
{
	class Transform;
	class FontComponent;
	class FontSystem
	{
	public:
		static void Init();
		static void Update(const float dt, const std::vector<EntityID>& entities, Transform* transform, FontComponent* _Sprite);

	};
}