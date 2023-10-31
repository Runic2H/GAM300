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
		.method("GetIsTrigger", &CapsuleCollider::GetIsTrigger)
		.method("SetIsTrigger", &CapsuleCollider::SetIsTrigger)
		.property("IsTrigger", &CapsuleCollider::mIsTrigger)
		.method("GetCenter", &CapsuleCollider::GetCenter)
		.method("SetCenter", rttr::select_overload<void(Vec3)>(&CapsuleCollider::SetCenter))
		.method("SetCenter", rttr::select_overload<void(float, float, float)>(&CapsuleCollider::SetCenter))
		.property("Center", &CapsuleCollider::mCenter)
		.method("GetRadius", &CapsuleCollider::GetRadius)
		.method("SetRadius", &CapsuleCollider::SetRadius)
		.property("Radius", &CapsuleCollider::mRadius)
		.method("GetHeight", &CapsuleCollider::GetHeight)
		.method("SetHeight", &CapsuleCollider::SetHeight)
		.property("Height", &CapsuleCollider::mHeight);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	CapsuleCollider::CapsuleCollider() : mIsTrigger(false),
		mCenter(Vec3(0.0f, 0.0f, 0.0f)),
		mRadius(0.5f),
		mHeight(2.0f),
		mDirection(Direction::Y_AXIS)
	{

		//CreateJPHCapsuleCollider(mHeight, mRadius); //height set to 10 and radius 5 by default, jph throws error when any value is <= 0
		//std::cout << "jph capsule collider created" << std::endl;


	}

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	CapsuleCollider::CapsuleCollider(CapsuleCollider&& toMove) noexcept : mIsTrigger(toMove.mIsTrigger),
		mCenter(toMove.mCenter),
		mRadius(toMove.mRadius),
		mHeight(toMove.mHeight),
		mDirection(toMove.mDirection)
	{ }


	CapsuleCollider* GetCapsuleCollider(EntityID entityID)
	{
		return ecs.getComponent<CapsuleCollider>(entityID);
	}

}