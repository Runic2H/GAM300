/*!*************************************************************************
****
\file collider.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Collider component class
****************************************************************************
***/

#include "components/collider.h"

namespace TDS 
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	Collider::Collider() : mColliderType	(ColliderType::NONE),
						   mCollisionNormal (Vec3(0.0f, 0.0f, 0.0f)),
						   mMin				(Vec3(0.0f, 0.0f, 0.0f)),
						   mMax				(Vec3(0.0f, 0.0f, 0.0f)),
						   mOffset			(Vec3(0.0f, 0.0f, 0.0f)),
						   mHit				(0),
						   mRadius			(0.0f),
						   mIsAlive			(true),
						   mCollision		(false)
	{ }

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	Collider::Collider(Collider&& toMove) noexcept : mColliderType(toMove.mColliderType),
													 mCollisionNormal(toMove.mCollisionNormal),
													 mMin(toMove.mMin),
													 mMax(toMove.mMax),
													 mOffset(toMove.mOffset),
													 mHit(toMove.mHit),
													 mRadius(toMove.mRadius),
													 mIsAlive(toMove.mIsAlive)
	{ }

	/*!*************************************************************************
	Deserializes the Collider component
	****************************************************************************/
	bool Collider::Deserialize(const rapidjson::Value& obj)
	{
		mColliderType		= static_cast<ColliderType>(obj["colliderType"].GetInt());
		mCollisionNormal	= Vec3(obj["collisionNormalX"].GetFloat(), obj["collisionNormalY"].GetFloat(), obj["collisionNormalZ"].GetFloat());
		mMin				= Vec3(obj["minX"].GetFloat(), obj["minY"].GetFloat(), obj["minZ"].GetFloat());
		mMax				= Vec3(obj["maxX"].GetFloat(), obj["maxY"].GetFloat(), obj["maxZ"].GetFloat());
		mOffset				= Vec3(obj["offsetX"].GetFloat(), obj["offsetY"].GetFloat(), obj["offsetZ"].GetFloat());
		mHit				= obj["hit"].GetInt();
		mRadius				= obj["radius"].GetFloat();
		mIsAlive			= obj["isAlive"].GetBool();

		return true;
	}

	/*!*************************************************************************
	Serializes the Collider component
	****************************************************************************/
	bool Collider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("colliderType");
		writer->Int(static_cast<int>(mColliderType));

		writer->Key("collisionNormalX");
		writer->Double(mCollisionNormal.x);
		writer->Key("collisionNormalY");
		writer->Double(mCollisionNormal.y);
		writer->Key("collisionNormalZ");
		writer->Double(mCollisionNormal.z);

		writer->Key("minX");
		writer->Double(mMin.x);
		writer->Key("minY");
		writer->Double(mMin.y);
		writer->Key("minZ");
		writer->Double(mMin.z);

		writer->Key("maxX");
		writer->Double(mMax.x);
		writer->Key("maxY");
		writer->Double(mMax.y);
		writer->Key("maxZ");
		writer->Double(mMax.z);

		writer->Key("offsetX");
		writer->Double(mOffset.x);
		writer->Key("offsetY");
		writer->Double(mOffset.y);
		writer->Key("offsetZ");
		writer->Double(mOffset.z);

		writer->Key("hit");
		writer->Int(mHit);

		writer->Key("radius");
		writer->Double(mRadius);

		writer->Key("isAlive");
		writer->Bool(mIsAlive);

		return true;
	}
}