#include "components/collider.h"

namespace TDS {
	/*!*************************************************************************
	Constructor for collider component
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
	Derserialize collider component
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
	Serialize collider component
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

	void Collider::ImGuiDisplay()
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Collider Type");

		ImGui::TableNextColumn();

		// Collider Type
		static std::string colliderTypeStringList[3]{ "None", "Circle", "Rectangle" };
		int colliderTypeSelected = static_cast<int>(mColliderType) - 1;

		// Uninitialized
		if (colliderTypeSelected == -1)
		{
			mColliderType = ColliderType::NONE;
			colliderTypeSelected = 0;
		}

		if (ImGui::BeginCombo("##", colliderTypeStringList[colliderTypeSelected].c_str()))
		{
			for (int n = 0; n < 3; n++)
			{
				const bool is_selected = (colliderTypeSelected == n);
				if (ImGui::Selectable(colliderTypeStringList[n].c_str(), is_selected))
				{
					mColliderType = static_cast<ColliderType>(n + 1);
				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImguiVec3Input("Collision Normal", mCollisionNormal);
		ImguiVec3Input("Min", mMin);
		ImguiVec3Input("Max", mMax);
		ImguiVec3Input("Offset", mOffset);
		ImguiIntInput("Hit", mHit);
		ImguiFloatInput("Radius", mRadius);
		ImguiBoolInput("Is Alive", mIsAlive);
	}
}