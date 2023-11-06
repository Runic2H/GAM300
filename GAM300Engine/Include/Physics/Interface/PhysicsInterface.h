/*!*****************************************************************************
 * \file          PhysicsInterface.h
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          07/11/2023
 * \brief         Interfacing for CLI to call Jolt Physics function
 *******************************************************************************/

#ifndef PHYSICSINTERFACE_H
#define PHYSICSINTERFACE_H

#include <Jolt/Physics/Body/BodyInterface.h>
#include "components/rigidBody.h"

namespace TDS
{
	/*!*************************************************************************
	 * Public Member Function
	 ***************************************************************************/
	void MoveKinematic(const RigidBody& rb, Vec3& inTargetPosition, Quat& inTargetRotation, float inDeltaTime);
	void SetLinearAndAngularVelocity(const RigidBody& rb, Vec3& inLinearVelocity, Vec3& inAngularVelocity);
	void GetLinearAndAngularVelocity(const RigidBody& rb, Vec3& outLinearVelocity, Vec3& outAngularVelocity);
	void SetLinearVelocity(const RigidBody& rb, Vec3& inLinearVelocity);
	Vec3 GetLinearVelocity(const RigidBody& rb);
	void AddLinearVelocity(const RigidBody& rb, Vec3& inLinearVelocity);
	void AddLinearAndAngularVelocity(const RigidBody& rb, Vec3& inLinearVelocity, Vec3& inAngularVelocity);
	void SetAngularVelocity(const RigidBody& rb, Vec3& inAngularVelocity);
	Vec3 GetAngularVelocity(const RigidBody& rb);
	Vec3 GetPointVelocity(const RigidBody& rb, Vec3& inPoint);
	void SetPositionRotationAndVelocity(const RigidBody& rb, Vec3& inPosition, Quat& inRotation, Vec3& inLinearVelocity, Vec3& inAngularVelocity);
	Mat4 GetInverseInertia(const RigidBody& rb);
	
	/*!*************************************************************************
	 * Position and rotation of a body
	 ***************************************************************************/
	void SetPositionAndRotation(const RigidBody& rb, Vec3& inPosition, Quat& inRotation, bool inActivate);
	void SetPositionAndRotationWhenChanged(const RigidBody& rb, Vec3& inPosition, Quat& inRotation, bool inActivate);
	void GetPositionAndRotation(const RigidBody& rb, Vec3& outPosition, Quat& outRotation);
	void SetPosition(const RigidBody& rb, Vec3& inPosition, bool inActivate);
	Vec3 GetPosition(const RigidBody& rb);
	Vec3 GetCenterOfMassPosition(const RigidBody& rb);
	void SetRotation(const RigidBody& rb, Quat& inRotation, bool inActivate);
	Quat GetRotation(const RigidBody& rb);
	Mat4 GetWorldTransform(const RigidBody& rb);
	Mat4 GetCenterOfMassTransform(const RigidBody& rb);

	/*!*************************************************************************
	 * Add forces to the body
	 ***************************************************************************/
	void AddForce(const RigidBody& rb, Vec3& inForce);
	void AddForce(const RigidBody& rb, Vec3& inForce, Vec3& inPoint);
	void AddTorque(const RigidBody& rb, Vec3& inTorque);
	void AddForceAndTorque(const RigidBody& rb, Vec3& inForce, Vec3& inTorque);
	
	/*!*************************************************************************
	 * Add an impulse to the body
	 ***************************************************************************/
	void AddImpulse(const RigidBody& rb, Vec3& inImpulse);
	void AddImpulse(const RigidBody& rb, Vec3& inImpulse, Vec3& inPoint);
	void AddAngularImpulse(const RigidBody& rb, Vec3& inAngularImpulse);
	
	/*!*************************************************************************
	 * Restitution 
	 ***************************************************************************/
	void SetRestitution(const RigidBody& rb, float inRestitution);
	float GetRestitution(const RigidBody& rb);

	/*!*************************************************************************
	 * Friction
	 ***************************************************************************/
	void SetFriction(const RigidBody& rb, float inFriction);
	float GetFriction(const RigidBody& rb);

	/*!*************************************************************************
	 * Gravity Factor
	 ***************************************************************************/
	void SetGravityFactor(const RigidBody& rb, float inGravityFactor);
	float GetGravityFactor(const RigidBody& rb);

}



#endif // !PHYSICSINTERFACE_H
