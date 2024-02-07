/*!*************************************************************************
****
\file boxCollider.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 21-10-2023
\brief  This program defines the functions in the Box Collider component
		class
****************************************************************************
***/

#include "components/boxCollider.h"

RTTR_REGISTRATION
{
	using namespace TDS;

rttr::registration::class_<BoxCollider>("Box Collider")
	.property("IsTrigger", &BoxCollider::mIsTrigger)
	.property("Collider Center", &BoxCollider::mColliderCenter)
	.property("Collider Size", &BoxCollider::mColliderSize)
	.property("Collider Scale", &BoxCollider::mColliderScale)
	.property("Offset Scale", &BoxCollider::mOffsetScale)
	.property("Offset Center", &BoxCollider::mOffsetCenter);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	BoxCollider::BoxCollider() : mIsTrigger(false),
		mColliderCenter(Vec3(0.0f, 0.0f, 0.0f)),
		mColliderSize(Vec3(1.0f, 1.0f, 1.0f)),
		mColliderScale(Vec3(1.0f, 1.0f, 1.0f)),
		mOffsetScale(Vec3(0.0f, 0.0f, 0.0f)),
		mOffsetCenter(Vec3(0.0f, 0.0f, 0.0f)),
		modelInit(false),
		modelScale(Vec3(1.0f, 1.0f, 1.0f)),
		modelCenter(Vec3(0.0f, 0.0f, 0.0f)),
		modelSize(Vec3(1.0f, 1.0f, 1.0f)),
		modelRotation(Vec3(0.0f, 0.0f, 0.0f))
	{
	}

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	BoxCollider::BoxCollider(BoxCollider&& toMove) noexcept : mIsTrigger(toMove.mIsTrigger),
		mColliderCenter(toMove.mColliderCenter),
		mColliderSize(toMove.mColliderSize),
		mColliderScale(toMove.mColliderScale),
		mOffsetScale(toMove.mOffsetScale),
		mOffsetCenter(toMove.mOffsetCenter),
		modelInit(toMove.modelInit),
		modelScale(toMove.modelScale),
		modelCenter(toMove.modelCenter),
		modelSize(toMove.modelSize),
		modelRotation(toMove.modelRotation)
	{ }

	BoxCollider* GetBoxCollider(EntityID entityID)
	{
		return ecs.getComponent<BoxCollider>(entityID);
	}
}