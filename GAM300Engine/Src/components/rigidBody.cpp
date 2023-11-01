/*!*************************************************************************
****
\file rigidBody.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the RigidBody component class
****************************************************************************
***/

#include "components/rigidBody.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<RigidBody>("Rigid Body")
		.method("GetMass", &RigidBody::GetMass)
		.method("SetMass", &RigidBody::SetMass)
		.property("Mass", &RigidBody::mMass)
		.method("GetAcceleration", &RigidBody::GetAcceleration)
		.method("SetAcceleration", &RigidBody::SetAcceleration)
		.property("Acceleration", &RigidBody::mAcceleration)
		.method("GetLinearVel", &RigidBody::GetLinearVel)
		.method("SetLinearVel", rttr::select_overload<void(Vec3)>(&RigidBody::SetLinearVel))
		.method("SetLinearVel", rttr::select_overload<void(float, float, float)>(&RigidBody::SetLinearVel))
		.property("Linear Velocity", &RigidBody::mLinearVelocity)
		.method("GetAngularVel", &RigidBody::GetAngularVel)
		.method("SetAngularVel", rttr::select_overload<void(Vec3)>(&RigidBody::SetAngularVel))
		.method("SetAngularVel", rttr::select_overload<void(float, float, float)>(&RigidBody::SetAngularVel))
		.property("Angular Velocity", &RigidBody::mAngularVelocity)
		.method("GetInputForce", &RigidBody::GetInputForce)
		.method("SetInputForce", rttr::select_overload<void(Vec3)>(&RigidBody::SetInputForce))
		.method("SetInputForce", rttr::select_overload<void(float, float, float)>(&RigidBody::SetInputForce))
		.property("Input Force", &RigidBody::mInputForce)
		.method("GetNormalizedForce", &RigidBody::GetNormalizedForce)
		.method("SetNormalizedForce", rttr::select_overload<void(Vec3)>(&RigidBody::SetNormalizedForce))
		.method("SetNormalizedForce", rttr::select_overload<void(float, float, float)>(&RigidBody::SetNormalizedForce))
		.property("Normalized Force", &RigidBody::mNormalizedForce)
		.method("GetDirection", &RigidBody::GetDirection)
		.method("SetDirection", rttr::select_overload<void(Vec3)>(&RigidBody::SetDirection))
		.method("SetDirection", rttr::select_overload<void(float, float, float)>(&RigidBody::SetDirection))
		.property("Direction", &RigidBody::mDirection)
		.method("GetNextPosition", &RigidBody::GetNextPosition)
		.method("SetNextPosition", &RigidBody::SetNextPosition)
		.property("Next Position", &RigidBody::mNextPosition)
		.method("GetFriction", &RigidBody::GetFriction)
		.method("SetFrictionCoefficient", &RigidBody::SetFrictionCoefficient)
		.property("Friction", &RigidBody::mFriction)
		.method("GetRestitution", &RigidBody::GetRestitution)
		.method("SetRestitution", &RigidBody::SetRestitution)
		.property("Restitution", &RigidBody::mRestitution)
		.method("GetInverseMass", &RigidBody::GetInverseMass)
		.method("setInverseMass", &RigidBody::setInverseMass)
		.property("Inverse Mass", &RigidBody::mInverseMass)
		.method("GetGravity", &RigidBody::GetGravity)
		.method("SetGravity", &RigidBody::SetGravity)
		.property("Gravity", &RigidBody::mGravity)
		.method("GetLinearDamping", &RigidBody::GetLinearDamping)
		.method("SetLinearDamping", &RigidBody::SetLinearDamping)
		.property("LinearDamping", &RigidBody::mLinearDamping)
		.method("GetAngularDamping", &RigidBody::GetAngularDamping)
		.method("GetAngularDamping", &RigidBody::SetAngularDamping)
		.property("AngularDamping", &RigidBody::mAngularDamping)
		.property("MotionType", &RigidBody::mMotionType);

	rttr::registration::enumeration<RigidBody::MotionType>("MotionType")
		(
			rttr::value("STATIC", RigidBody::MotionType::STATIC),
			rttr::value("DYNAMIC", RigidBody::MotionType::DYNAMIC),
			rttr::value("KINEMATIC", RigidBody::MotionType::KINEMATIC)
		);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the RigidBody component when created
	****************************************************************************/
	RigidBody::RigidBody() : mAcceleration(Vec3(0.0f, 0.0f, 0.0f)),
							 mLinearVelocity(Vec3(0.0f, 0.0f, 0.0f)),
							 mAngularVelocity(Vec3(0.0f, 0.0f, 0.0f)),
							 mDirection(Vec3(0.0f, 0.0f, 0.0f)),
							 mNextPosition(Vec3(0.0f, 0.0f, 0.0f)),
							 mInputForce(Vec3(0.0f, 0.0f, 0.0f)),
							 mNormalizedForce(Vec3(0.0f, 0.0f, 0.0f)),
							 mFriction(0.2f),
							 mRestitution(0.0f),
							 mMass(1.0f),
							 mInverseMass(0.0f),
							 mGravity(0.0f),
							 mLinearDamping(0.05f),
							 mAngularDamping(0.05f),
							 mBodyID(JoltBodyID()),
							 mMotionType(MotionType::STATIC)
	{ }


	/*!*************************************************************************
	Initializes the RigidBody component when created, given another RigidBody
	component to move (for ECS)
	****************************************************************************/
	RigidBody::RigidBody(RigidBody&& toMove) noexcept : mAcceleration(toMove.mAcceleration),
														mLinearVelocity(toMove.mLinearVelocity),
														mAngularVelocity(toMove.mAngularVelocity),
														mDirection(toMove.mDirection),
														mNextPosition(toMove.mNextPosition),
														mInputForce(toMove.mInputForce),
														mNormalizedForce(toMove.mNormalizedForce),
														mFriction(toMove.mFriction),
														mRestitution(toMove.mRestitution),
														mMass(toMove.mMass),
														mInverseMass(toMove.mInverseMass),
														mGravity(toMove.mGravity),
														mBodyID(toMove.mBodyID),
														mMotionType(toMove.mMotionType)

	{ }

}