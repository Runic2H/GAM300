#include "components/transform.h"

namespace TDS
{
	Transform::Transform() : mPosition	(Vec3(0.0f, 0.0f, 0.0f)), 
							 mScale		(Vec3(1.0f, 1.0f, 0.0f)),
							 mRotation	(0.0f)
	{ }

	bool Transform::Deserialize(const rapidjson::Value& obj)
	{
		mPosition = Vec3(obj["positionX"].GetFloat(), obj["positionY"].GetFloat(), obj["positionZ"].GetFloat());
		mScale = Vec3(obj["scaleX"].GetFloat(), obj["scaleY"].GetFloat(), obj["scaleZ"].GetFloat());
		mRotation = obj["rotation"].GetFloat();

		return true;
	}

	bool Transform::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("positionX");
		writer->Double(mPosition.x);
		writer->Key("positionY");
		writer->Double(mPosition.y);
		writer->Key("positionZ");
		writer->Double(mPosition.z);

		writer->Key("scaleX");
		writer->Double(mScale.x);
		writer->Key("scaleY");
		writer->Double(mScale.y);
		writer->Key("scaleZ");
		writer->Double(mScale.z);

		writer->Key("rotation");
		writer->Double(mRotation);

		return true;
	}

	void Transform::ImGuiDisplay()
	{
		ImguiVec3Input("Position", mPosition);
		ImguiVec3Input("Scale", mScale);
		ImguiFloatInput("Rotation", mRotation);
	}
}
