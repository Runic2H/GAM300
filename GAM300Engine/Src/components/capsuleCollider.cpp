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

	/*!*************************************************************************
	Deserializes the Collider component
	****************************************************************************/
	bool CapsuleCollider::Deserialize(const rapidjson::Value& obj)
	{
		mIsTrigger = obj["isTrigger"].GetBool();
		mCenter = Vec3(obj["centerX"].GetFloat(), obj["centerY"].GetFloat(), obj["centerZ"].GetFloat());
		mRadius = obj["radius"].GetFloat();
		mHeight = obj["height"].GetFloat();
		mDirection = static_cast<Direction>(obj["height"].GetInt());

		return true;
	}

	/*!*************************************************************************
	Serializes the Collider component
	****************************************************************************/
	bool CapsuleCollider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("isTrigger");
		writer->Bool(mIsTrigger);

		writer->Key("centerX");
		writer->Double(mCenter.x);
		writer->Key("centerY");
		writer->Double(mCenter.y);
		writer->Key("centerZ");
		writer->Double(mCenter.z);

		writer->Key("radius");
		writer->Double(mRadius);

		writer->Key("height");
		writer->Double(mHeight);

		writer->Key("direction");
		writer->Int(static_cast<int>(mDirection));

		return true;
	}

	CapsuleCollider* GetCapsuleCollider(EntityID entityID)
	{
		return ecs.getComponent<CapsuleCollider>(entityID);
	}
}