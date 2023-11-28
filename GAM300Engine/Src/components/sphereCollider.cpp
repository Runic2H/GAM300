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
		.property("IsInteract", &SphereCollider::mIsInteract)
		.property("Center", &SphereCollider::mCenter)
		.property("Radius", &SphereCollider::mRadius)
		.property("AImode", &SphereCollider::AI)
		.property("ColliderName", &SphereCollider::mColliderName);
		
	rttr::registration::enumeration<SphereCollider::AImode>("AImode")
		(
			rttr::value("NONE", SphereCollider::AImode::NONE),
			rttr::value("MONSTER", SphereCollider::AImode::MONSTER),
			rttr::value("PLAYER", SphereCollider::AImode::PLAYER),
			rttr::value("INTERACTABLE", SphereCollider::AImode::INTERACTABLE)
		);


}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	SphereCollider::SphereCollider() : mIsTrigger(false),
									mIsInteract(false),
									mCenter(Vec3(0.0f, 0.0f, 0.0f)),
									mRadius(0.5f),
									AI(AImode::NONE),
									mColliderName("")
	{
		//CreateJPHSphereCollider(mRadius);

	}

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	SphereCollider::SphereCollider(SphereCollider&& toMove) noexcept : mIsTrigger(toMove.mIsTrigger),
																		mIsInteract(toMove.mIsInteract),
																		mCenter(toMove.mCenter),
																		mRadius(toMove.mRadius),
																		AI(toMove.AI),
																		mColliderName(toMove.mColliderName)
	{ }



	SphereCollider* GetSphereCollider(EntityID entityID)
	{
		return ecs.getComponent<SphereCollider>(entityID);
	}
	
}