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
		.method("GetIsTrigger", &SphereCollider::GetIsTrigger)
		.method("SetIsTrigger", &SphereCollider::SetIsTrigger)
		.property("IsTrigger", &SphereCollider::mIsTrigger)
		.method("GetCenter", &SphereCollider::GetCenter)
		.method("SetCenter", rttr::select_overload<void(Vec3)>(&SphereCollider::SetCenter))
		.method("SetCenter", rttr::select_overload<void(float, float, float)>(&SphereCollider::SetCenter))
		.property("Center", &SphereCollider::mCenter)
		.method("GetRadius", &SphereCollider::GetRadius)
		.method("SetRadius", &SphereCollider::SetRadius)
		.property("Radius", &SphereCollider::mRadius);

}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	SphereCollider::SphereCollider() : mIsTrigger	(false),
									   mCenter		(Vec3(0.0f, 0.0f, 0.0f)),
									   mRadius		(0.0f)
	{ }

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	SphereCollider::SphereCollider(SphereCollider&& toMove) noexcept : mIsTrigger	(toMove.mIsTrigger),
																	   mCenter		(toMove.mCenter),
																	   mRadius		(toMove.mRadius)
	{ }

	SphereCollider* GetSphereCollider(EntityID entityID)
	{
		return ecs.getComponent<SphereCollider>(entityID);
	}
}