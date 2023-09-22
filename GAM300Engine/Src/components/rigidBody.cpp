#include "components/rigidBody.h"

namespace TDS
{
	/*!*************************************************************************
	Ctor for RigidBody Component
	****************************************************************************/
	RigidBody::RigidBody() : mAcceleration	(Vec2(1.0f,1.0f)),
							 mVelocity		(Vec2(1.0f,1.0f)), 
							 mDirection		(Vec2(1.0f,0.0f)), 
							 mNextPosition	(Vec2(1.0f,0.0f)), 
							 mFriction		(0.0f),
							 mRestitution	(0.0f) 
	{ }

	/*!*************************************************************************
	Deserialize for RigidBody
	****************************************************************************/
	bool RigidBody::Deserialize(const rapidjson::Value& obj)
	{
		mAcceleration	= Vec2(obj["accelerationX"].GetFloat(), obj["accelerationY"].GetFloat());
		mVelocity		= Vec2(obj["velocityX"].GetFloat(), obj["velocityY"].GetFloat());
		mDirection		= Vec2(obj["directionX"].GetFloat(), obj["directionY"].GetFloat());
		mNextPosition	= Vec2(obj["nextPositionX"].GetFloat(), obj["nextPositionY"].GetFloat());
		mFriction		= obj["friction"].GetFloat();
		mRestitution	= obj["restitution"].GetFloat();
		return true;
	}

	/*!*************************************************************************
	Serialize for RigidBody
	****************************************************************************/
	bool RigidBody::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("accelerationX");
		writer->Double(mAcceleration.x);
		writer->Key("accelerationY");
		writer->Double(mAcceleration.y);
		
		writer->Key("velocityX");
		writer->Double(mVelocity.x);
		writer->Key("velocityY");
		writer->Double(mVelocity.y);

		writer->Key("directionX");
		writer->Double(mDirection.x);
		writer->Key("directionY");
		writer->Double(mDirection.y);

		writer->Key("nextPositionX");
		writer->Double(mNextPosition.x);
		writer->Key("nextPositionY");
		writer->Double(mNextPosition.y);

		writer->Key("friction");
		writer->Double(mFriction);

		writer->Key("restitution");
		writer->Double(mRestitution);

		return true;
	}

	void RigidBody::ImGuiDisplay()
	{
		ImguiVec2Input("Acceleration", mAcceleration);
		ImguiVec2Input("Velocity", mVelocity);
		ImguiVec2Input("Direction", mDirection);
		ImguiVec2Input("Next Position", mNextPosition);
		ImguiFloatInput("Friction", mFriction);
		ImguiFloatInput("Restitution", mRestitution);
	}
}