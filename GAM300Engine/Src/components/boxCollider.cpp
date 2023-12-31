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
		.property("Center", &BoxCollider::mCenter)
		.property("Size", &BoxCollider::mSize);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	BoxCollider::BoxCollider() : mIsTrigger(false),
		mCenter(Vec3(0.0f, 0.0f, 0.0f)),
		mSize(Vec3(1.0f, 1.0f, 1.0f))
	{
		//half extents are all half of size
		JPH::Vec3 halfextents = JPH::Vec3(mSize.x * 0.5f, mSize.y * 0.5f, mSize.z * 0.5f);
		//CreateJPHBoxCollider(halfextents, JPH::cDefaultConvexRadius);
	}

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	BoxCollider::BoxCollider(BoxCollider&& toMove) noexcept : mIsTrigger(toMove.mIsTrigger),
		mCenter(toMove.mCenter),
		mSize(toMove.mSize)
	{ }

	BoxCollider* GetBoxCollider(EntityID entityID)
	{
		return ecs.getComponent<BoxCollider>(entityID);
	}
}