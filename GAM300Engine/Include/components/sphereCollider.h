/*!*************************************************************************
****
\file capsuleCollider.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 21-10-2023
\brief  This program declares the functions in the Capsule Collider
		component class
****************************************************************************
***/

#ifndef SPHERECOLLIDERCOMPONENT
#define SPHERECOLLIDERCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class SphereCollider : public IComponent
	{
	public:

		/*!*************************************************************************
		Initializes the Collider component when created
		****************************************************************************/
		DLL_API SphereCollider();
		/*!*************************************************************************
		Initializes the Collider component when created, given another Collider
		component to move (for ECS)
		****************************************************************************/
		DLL_API SphereCollider(SphereCollider&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Collider component class
		****************************************************************************/
		DLL_API ~SphereCollider() = default;
		/*!*************************************************************************
		Getter and setter functions for the variables in the Collider component class
		****************************************************************************/
		DLL_API bool& GetIsTrigger() { return mIsTrigger; }
		DLL_API void SetIsTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

		DLL_API Vec3& GetColliderCenter() { return mColliderCenter; }
		DLL_API void SetColliderCenter(Vec3 center) { mColliderCenter = center; }
		DLL_API void SetColliderCenter(float x, float y, float z) { mColliderCenter = Vec3(x, y, z); }

		DLL_API float& GetColliderRadius() { return mColliderRadius; }
		DLL_API void SetColliderRadius(float radius) { mColliderRadius = radius; }

		DLL_API float& GetRadiusFactor() { return mRadiusFactor; }
		DLL_API void SetRadiusFactor(float radiusFactor) { mRadiusFactor = radiusFactor; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		bool mIsTrigger;
		//Material mMaterial;
		Vec3 mColliderCenter;
		float mRadiusFactor;
		float mColliderRadius;

	};

	DLL_API SphereCollider* GetSphereCollider(EntityID entityID);
}

#endif
