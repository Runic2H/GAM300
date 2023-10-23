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

	/*!*************************************************************************
	Deserializes the Collider component
	****************************************************************************/
	bool SphereCollider::Deserialize(const rapidjson::Value& obj)
	{
		mIsTrigger = obj["isTrigger"].GetBool();
		mCenter = Vec3(obj["centerX"].GetFloat(), obj["centerY"].GetFloat(), obj["centerZ"].GetFloat());
		mRadius = obj["radius"].GetFloat();

		return true;
	}

	/*!*************************************************************************
	Serializes the Collider component
	****************************************************************************/
	bool SphereCollider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
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

		return true;
	}

	SphereCollider* GetSphereCollider(EntityID entityID)
	{
		return ecs.getComponent<SphereCollider>(entityID);
	}
}