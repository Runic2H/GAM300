#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"

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

		//void MoveKinematic(Vector3& inTargetPosition, Quat& inTargetRotation, float inDeltaTime);
		void SetLinearAndAngularVelocity(Vector3 linearVelocity, Vector3 angularVelocity);
		void GetLinearAndAngularVelocity(Vector3& outLinearVelocity, Vector3& outAngularVelocity);
		void SetLinearVelocity(Vector3& inLinearVelocity);
		Vector3 GetLinearVelocity();
		void AddLinearVelocity(Vector3& inLinearVelocity);
		void AddLinearAndAngularVelocity(Vector3& inLinearVelocity, Vector3& inAngularVelocity);
		void SetAngularVelocity(Vector3& inAngularVelocity);
		Vector3 GetAngularVelocity();
		Vector3 GetPointVelocity(Vector3& inPoint);
		//void SetPositionRotationAndVelocity(Vector3& inPosition, Quat& inRotation, Vector3& inLinearVelocity, Vector3& inAngularVelocity);

	internal:
		RigidBodyComponent(TDS::EntityID ID);

	private:
		TDS::EntityID entityID;
	};
}