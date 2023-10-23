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

	/*!*************************************************************************
	Deserializes the Collider component
	****************************************************************************/
	bool BoxCollider::Deserialize(const rapidjson::Value& obj)
	{
		mIsTrigger = obj["isTrigger"].GetBool();
		mCenter = Vec3(obj["centerX"].GetFloat(), obj["centerY"].GetFloat(), obj["centerZ"].GetFloat());
		mSize = Vec3(obj["sizeX"].GetFloat(), obj["sizeY"].GetFloat(), obj["sizeZ"].GetFloat());

		return true;
	}

	/*!*************************************************************************
	Serializes the Collider component
	****************************************************************************/
	bool BoxCollider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("isTrigger");
		writer->Bool(mIsTrigger);

		writer->Key("centerX");
		writer->Double(mCenter.x);
		writer->Key("centerY");
		writer->Double(mCenter.y);
		writer->Key("centerZ");
		writer->Double(mCenter.z);

		writer->Key("sizeX");
		writer->Double(mSize.x);
		writer->Key("sizeY");
		writer->Double(mSize.y);
		writer->Key("sizeZ");
		writer->Double(mSize.z);

		return true;
	}

	BoxCollider* GetBoxCollider(EntityID entityID)
	{
		return ecs.getComponent<BoxCollider>(entityID);
	}
}