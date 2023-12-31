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
		.property("Position", &Transform::mPosition)
		.property("Scale", &Transform::mScale)
		.property("Rotation", &Transform::mRotation);
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

	Vec4 Transform::getLocalPosition(EntityID parent)
	{
		if (parent)
		{
			Mat4 parentTransformationMatrix = GetTransform(parent)->GenerateTransform().inverse();
			Vec4 localPosition = parentTransformationMatrix * Vec4(mPosition, 1.f);

			localPosition.x /= localPosition.w;
			localPosition.y /= localPosition.w;
			localPosition.z /= localPosition.w;

			return localPosition;
		}

		return mPosition;
	}
	void Transform::setLocalPosition(EntityID parent, Vec4 localPosition)
	{
		localPosition.x *= localPosition.w;
		localPosition.y *= localPosition.w;
		localPosition.z *= localPosition.w;

		mPosition = GetTransform(parent)->GenerateTransform() * localPosition;
	}

	Vec4 Transform::getLocalScale(EntityID parent)
	{
		Mat4 parentTransformationMatrix = GetTransform(parent)->GenerateTransform().inverse();
		Vec4 localScale = parentTransformationMatrix * Vec4(mScale, 1.f);

		localScale.x /= localScale.w;
		localScale.y /= localScale.w;
		localScale.z /= localScale.w;

		return localScale;
	}
	void Transform::setLocalScale(EntityID parent, Vec4 localScale)
	{
		localScale.x *= localScale.w;
		localScale.y *= localScale.w;
		localScale.z *= localScale.w;

		mPosition = GetTransform(parent)->GenerateTransform() * localScale;
	}

	Vec4 Transform::getLocalRotation(EntityID parent)
	{
		Mat4 parentTransformationMatrix = GetTransform(parent)->GenerateTransform().inverse();
		Vec4 localRotation = parentTransformationMatrix * Vec4(mRotation, 1.f);

		localRotation.x /= localRotation.w;
		localRotation.y /= localRotation.w;
		localRotation.z /= localRotation.w;

		return localRotation;
	}
	void Transform::setLocalRotation(EntityID parent, Vec4 localRotation)
	{
		localRotation.x *= localRotation.w;
		localRotation.y *= localRotation.w;
		localRotation.z *= localRotation.w;

		mPosition = GetTransform(parent)->GenerateTransform() * localRotation;
	}

	Transform* GetTransform(EntityID entityID)
	{
		return ecs.getComponent<Transform>(entityID);
	}
}
