#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"
#include "../Vector4.hxx"

namespace ScriptAPI
{
	public value class RigidBodyComponent
	{
	public:
		enum class MotionType
		{
			STATIC,
			KINEMATIC,
			DYNAMIC
		};

		void MoveKinematic(Vector3 inTargetPosition, Vector4 inTargetRotation, float inDeltaTime);
		void SetLinearAndAngularVelocity(Vector3 linearVelocity, Vector3 angularVelocity);
		void GetLinearAndAngularVelocity(Vector3& outLinearVelocity, Vector3& outAngularVelocity);
		void SetLinearVelocity(Vector3 inLinearVelocity);
		Vector3 GetLinearVelocity();
		void AddLinearVelocity(Vector3 inLinearVelocity);
		void AddLinearAndAngularVelocity(Vector3 inLinearVelocity, Vector3 inAngularVelocity);
		void SetAngularVelocity(Vector3 inAngularVelocity);
		Vector3 GetAngularVelocity();
		Vector3 GetPointVelocity(Vector3& inPoint);
		void SetPositionRotationAndVelocity(Vector3 inPosition, Vector4 inRotation, Vector3 inLinearVelocity, Vector3 inAngularVelocity);

		// FORCES
		void AddForce(Vector3 inForce);
		void AddForce(Vector3 inForce, Vector3 inPoint);
		void AddTorque(Vector3 inTorque);
		void AddForceAndTorque(Vector3 inForce, Vector3 inTorque);

		// IMPLUSES
		void AddImpulse(Vector3 inImpulse);
		void AddImpulse(Vector3 inImpulse, Vector3 inPoint);
		void AddAngularImpulse(Vector3 inAngularImpulse);

		// RESTITUTION
		void SetRestitution(float inRestitution);
		float GetRestitution();

		// RESTITUTION
		void SetFriction(float inFriction);
		float GetFriction();

		// RESTITUTION
		void SetGravityFactor(float inGravityFactor);
		float GetGravityFactor();

	internal:
		RigidBodyComponent(TDS::EntityID ID);

	private:
		TDS::EntityID entityID;
	};
}