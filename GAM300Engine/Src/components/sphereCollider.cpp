/*!*************************************************************************
****
\file sphereCollider.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 21-10-2023
\brief  This program defines the functions in the Sphere Collider component
		class
****************************************************************************
***/

#include "components/sphereCollider.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<SphereCollider>("Sphere Collider")
		.property("IsTrigger", &SphereCollider::mIsTrigger)
		.property("Collider Center", &SphereCollider::mColliderCenter)
		.property("Collider Radius", &SphereCollider::mColliderRadius)
		.property("Radius Factor", &SphereCollider::mRadiusFactor);
		
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	SphereCollider::SphereCollider() : mIsTrigger(false),
									mColliderCenter(Vec3(0.0f, 0.0f, 0.0f)),
									mColliderRadius(1.0f),
									mRadiusFactor(1.0f)
	{
	}

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	SphereCollider::SphereCollider(SphereCollider&& toMove) noexcept : mIsTrigger(toMove.mIsTrigger),
																		mColliderCenter(toMove.mColliderCenter),
																		mColliderRadius(toMove.mColliderRadius),
																		mRadiusFactor(toMove.mRadiusFactor)
	{ }



	SphereCollider* GetSphereCollider(EntityID entityID)
	{
		return ecs.getComponent<SphereCollider>(entityID);
	}
	
}