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
		.property("Position", &Transform::GetPosition, rttr::select_overload<void(Vec3)>(&Transform::SetPosition))
		.property("Scale", &Transform::GetScale, rttr::select_overload<void(Vec3)>(&Transform::SetScale))
		.property("Rotation", &Transform::GetRotation, rttr::select_overload<void(Vec3)>(&Transform::SetRotation));
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Transform component when created
	****************************************************************************/
	Transform::Transform() : mPosition(Vec3(0.0f, 0.0f, 0.0f)),
							mScale(Vec3(1.0f, 1.0f, 1.0f)),
							mRotation(Vec3(0.0f, 0.f, 0.0f)),
							mTransformMatrix(Mat4::zero()),
							mOffsetScale(Vec3(0.f, 0.f, 0.f)),
							mOffsetPos(Vec3(0.f, 0.f, 0.f)),
							mOffsetMatrix(Mat4::zero())
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
