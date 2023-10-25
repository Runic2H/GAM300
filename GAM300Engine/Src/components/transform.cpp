/*!*************************************************************************
****
\file transform.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Transform component class
****************************************************************************
***/

#include "components/transform.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<Transform>("Transform")
		.method("GetPosition", &Transform::GetPosition)
		.method("SetPosition", rttr::select_overload<void(Vec3)>(&Transform::SetPosition))
		.method("SetPosition", rttr::select_overload<void(float, float, float)>(&Transform::SetPosition))
		.property("Position", &Transform::mPosition)//, rttr::registration::private_access)
		.method("GetScale", &Transform::GetScale)
		.method("SetScale", rttr::select_overload<void(Vec3)>(&Transform::SetScale))
		.method("SetScale", rttr::select_overload<void(float, float, float)>(&Transform::SetScale))
		.property("Scale", &Transform::mScale)//, rttr::registration::private_access)
		.method("GetRotation", &Transform::GetRotation)
		.method("SetRotation", rttr::select_overload<void(Vec3)>(&Transform::SetRotation))
		.method("SetRotation", rttr::select_overload<void(float, float, float)>(&Transform::SetRotation))
		.property("Rotation", &Transform::mRotation);//, rttr::registration::private_access);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Transform component when created
	****************************************************************************/
	Transform::Transform() : mPosition			(Vec3(0.0f, 0.0f, 0.0f)), 
							 mScale				(Vec3(1.0f, 1.0f, 0.0f)),
							 mRotation			(Vec3(0.0f, 0.f,0.0f)),
							 mTransformMatrix	(Mat4::zero())
	{ }

	/*!*************************************************************************
	Initializes the Transform component when created, given another Transform
	component to move (for ECS)
	****************************************************************************/
	Transform::Transform(Transform&& toMove) noexcept : mPosition			(toMove.mPosition),
														mScale				(toMove.mScale),
														mRotation			(toMove.mRotation),
														mTransformMatrix	(toMove.mTransformMatrix)
	{ }

	Transform* GetTransform(EntityID entityID)
	{
		return ecs.getComponent<Transform>(entityID);
	}
}
