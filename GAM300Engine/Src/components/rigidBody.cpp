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
#include <Jolt/Physics/Body/Body.h>

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<RigidBody>("Rigid Body");
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the RigidBody component when created
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
							 mGravity			(0.0f),
							 mBodyID			(JPH::BodyID::cInvalidBodyID)
	{ }


	/*!*************************************************************************
	Initializes the RigidBody component when created, given another RigidBody
	component to move (for ECS)
	****************************************************************************/
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
														mGravity			(toMove.mGravity),
														mBodyID				(toMove.mBodyID)
		
	{ }
}