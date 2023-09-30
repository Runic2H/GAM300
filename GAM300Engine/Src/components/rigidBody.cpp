#include "components/rigidBody.h"

namespace TDS
{
	/*!*************************************************************************
	Ctor for RigidBody Component
	****************************************************************************/
	RigidBody::RigidBody() : mAcceleration		(Vec3(0.0f, 0.0f, 0.0f)),
							 mLinearVelocity	(Vec3(0.0f, 0.0f, 0.0f)),
							 mAngularVelocity	(Vec3(0.0f, 0.0f, 0.0f)),
							 mDirection			(Vec3(0.0f, 0.0f, 0.0f)),
							 mNextPosition		(Vec3(0.0f, 0.0f, 0.0f)),
							 mInputForce		(Vec3(0.0f, 0.0f, 0.0f)),
							 mNormalizedForce	(Vec3(0.0f, 0.0f, 0.0f)),
							 mFriction			(0.0f),
							 mRestitution		(0.0f),
						     mMass				(1.0f),
							 mInverseMass		(0.0f),
							 mGravity			(0.0f)
	{ }


	RigidBody::RigidBody(RigidBody&& toMove) noexcept : mAcceleration		(toMove.mAcceleration),
														mLinearVelocity		(toMove.mLinearVelocity),
														mAngularVelocity	(toMove.mAngularVelocity),
														mDirection			(toMove.mDirection),
														mNextPosition		(toMove.mNextPosition),
														mInputForce			(toMove.mInputForce),
														mNormalizedForce	(toMove.mNormalizedForce),
														mFriction			(toMove.mFriction),
														mRestitution		(toMove.mRestitution),
														mMass				(toMove.mMass),
														mInverseMass		(toMove.mInverseMass),
														mGravity			(toMove.mGravity)
		
	{ }

	/*!*************************************************************************
	Deserialize for RigidBody
	****************************************************************************/
	bool RigidBody::Deserialize(const rapidjson::Value& obj)
	{
		mAcceleration		= Vec3(obj["accelerationX"].GetFloat(), obj["accelerationY"].GetFloat(), obj["accelerationZ"].GetFloat());
		mLinearVelocity		= Vec3(obj["linearvelocityX"].GetFloat(), obj["linearvelocityY"].GetFloat(), obj["linearvelocityZ"].GetFloat());
		mAngularVelocity	= Vec3(obj["angularvelocityX"].GetFloat(), obj["angularvelocityY"].GetFloat(), obj["angularvelocityZ"].GetFloat());
		mDirection			= Vec3(obj["directionX"].GetFloat(), obj["directionY"].GetFloat(), obj["directionZ"].GetFloat());
		mInputForce			= Vec3(obj["inputForceX"].GetFloat(), obj["inputForceY"].GetFloat(), obj["inputForceZ"].GetFloat());
		mNormalizedForce	= Vec3(obj["normalizedForceX"].GetFloat(), obj["normalizedForceY"].GetFloat(), obj["normalizedForceZ"].GetFloat());
		mNextPosition		= Vec3(obj["nextPositionX"].GetFloat(), obj["nextPositionY"].GetFloat(), obj["nextPositionZ"].GetFloat());
		mFriction			= obj["friction"].GetFloat();
		mRestitution		= obj["restitution"].GetFloat();
		mMass				= obj["mass"].GetFloat();
		mInverseMass		= obj["inverseMass"].GetFloat();
		mGravity			= obj["gravity"].GetFloat();
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
		writer->Key("accelerationZ");
		writer->Double(mAcceleration.z);
		
		writer->Key("linearvelocityX");
		writer->Double(mLinearVelocity.x);
		writer->Key("linearvelocityY");
		writer->Double(mLinearVelocity.y);
		writer->Key("linearvelocityZ");
		writer->Double(mLinearVelocity.z);
		
		writer->Key("angularvelocityX");
		writer->Double(mAngularVelocity.x);
		writer->Key("angularvelocityY");
		writer->Double(mAngularVelocity.y);
		writer->Key("angularvelocityZ");
		writer->Double(mAngularVelocity.z);

		writer->Key("directionX");
		writer->Double(mDirection.x);
		writer->Key("directionY");
		writer->Double(mDirection.y);
		writer->Key("directionZ");
		writer->Double(mDirection.z);

		writer->Key("nextPositionX");
		writer->Double(mNextPosition.x);
		writer->Key("nextPositionY");
		writer->Double(mNextPosition.y);
		writer->Key("nextPositionZ");
		writer->Double(mNextPosition.z);

		writer->Key("inputForceX");
		writer->Double(mInputForce.x);
		writer->Key("inputForceY");
		writer->Double(mInputForce.y);
		writer->Key("inputForceZ");
		writer->Double(mInputForce.z);
		
		writer->Key("normalizedForceX");
		writer->Double(mNormalizedForce.x);
		writer->Key("normalizedForceY");
		writer->Double(mNormalizedForce.y);
		writer->Key("normalizedForceZ");
		writer->Double(mNormalizedForce.z);
		
		writer->Key("friction");
		writer->Double(mFriction);

		writer->Key("restitution");
		writer->Double(mRestitution);

		writer->Key("mass");
		writer->Double(mMass);

		writer->Key("inverseMass");
		writer->Double(mInverseMass);

		writer->Key("gravity");
		writer->Double(mGravity);

		return true;
	}

	//void RigidBody::ImGuiDisplay()
	//{
	//	ImguiVec3Input("Input Force", mInputForce);
	//	ImguiVec3Input("Linear Velocity", mLinearVelocity);
	//	ImguiVec3Input("Angular Velocity", mAngularVelocity);
	//	ImguiVec3Input("Acceleration", mAcceleration);
	//	ImguiVec3Input("Direction", mDirection);
	//	ImguiVec3Input("Next Position", mNextPosition);
	//	ImguiFloatInput("Friction", mFriction);
	//	ImguiFloatInput("Restitution", mRestitution);
	//	ImguiFloatInput("Mass", mMass);
	//	ImguiFloatInput("Gravity", mGravity);
	//}
}