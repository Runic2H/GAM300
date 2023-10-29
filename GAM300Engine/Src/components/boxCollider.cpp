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

	//rttr::registration::property()

	rttr::registration::class_<BoxCollider>("Box Collider")
		.property("IsTrigger", &BoxCollider::GetIsTrigger, &BoxCollider::SetIsTrigger)
		.method("GetCenter", &BoxCollider::GetCenter)
		.property("Center", &BoxCollider::GetCenter, rttr::select_overload<void(Vec3)>(&BoxCollider::SetCenter))
		.property("Size", &BoxCollider::GetSize, rttr::select_overload<void(Vec3)>(&BoxCollider::SetSize));
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	BoxCollider::BoxCollider() : mIsTrigger		(false),
								 mCenter		(Vec3(0.0f, 0.0f, 0.0f)),
								 mSize			(Vec3(0.0f, 0.0f, 0.0f))
	{ }

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	BoxCollider::BoxCollider(BoxCollider&& toMove) noexcept : mIsTrigger	(toMove.mIsTrigger),
															  mCenter		(toMove.mCenter),
															  mSize			(toMove.mSize)
	{ }

	BoxCollider* GetBoxCollider(EntityID entityID)
	{
		return ecs.getComponent<BoxCollider>(entityID);
	}
}