/*!*************************************************************************
****
\file capsuleCollider.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 21-10-2023
\brief  This program defines the functions in the Capsule Collider component 
		class
****************************************************************************
***/

#include "components/capsuleCollider.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::enumeration<CapsuleCollider::Direction>("Direction")
	(
		rttr::value("X_AXIS", CapsuleCollider::Direction::X_AXIS),
		rttr::value("Y_AXIS", CapsuleCollider::Direction::Y_AXIS),
		rttr::value("Z_AXIS", CapsuleCollider::Direction::Z_AXIS)
	);

	rttr::registration::class_<CapsuleCollider>("Capsule Collider")
		.property("IsTrigger", &CapsuleCollider::GetIsTrigger, &CapsuleCollider::SetIsTrigger)
		.property("Center", &CapsuleCollider::GetCenter, rttr::select_overload<void(Vec3)>(&CapsuleCollider::SetCenter))
		.property("Radius", &CapsuleCollider::GetRadius, &CapsuleCollider::SetRadius)
		.property("Height", &CapsuleCollider::GetHeight, &CapsuleCollider::SetHeight);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	CapsuleCollider::CapsuleCollider() : mIsTrigger		(false),
										 mCenter		(Vec3(0.0f, 0.0f, 0.0f)),
										 mRadius		(0.0f),
										 mHeight		(0.0f),
										 mDirection		(Direction::X_AXIS)
	{ }

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	CapsuleCollider::CapsuleCollider(CapsuleCollider&& toMove) noexcept : mIsTrigger	(toMove.mIsTrigger),
																		  mCenter		(toMove.mCenter),
																		  mRadius		(toMove.mRadius),
																		  mHeight		(toMove.mHeight),
																		  mDirection	(toMove.mDirection)
	{ }

	CapsuleCollider* GetCapsuleCollider(EntityID entityID)
	{
		return ecs.getComponent<CapsuleCollider>(entityID);
	}
}