#include "RigidBodyComponent.hxx"
#include "Physics/Interface/PhysicsInterface.h"
#include "../Shared_Libs/Vector3.h"

namespace ScriptAPI
{
	//void MoveKinematic(Vector3& inTargetPosition, Quat& inTargetRotation, float inDeltaTime);
	void RigidBodyComponent::SetLinearAndAngularVelocity(Vector3 linearVelocity, Vector3 angularVelocity)
	{
		// May wanna change to a function
		if (!TDS::GetRigidBody(entityID))
		{
			// throw error instead (not sure how)
			return;
		}

		//TDS::Vec3 linearVelocityVec3;
		//linearVelocityVec3.x = linearVelocity.X;
		//linearVelocityVec3.y = linearVelocity.Y;
		//linearVelocityVec3.z = linearVelocity.Z;
		//TDS::Vec3 angularVelocityVec3; // (angularVelocity.X, angularVelocity.Y, angularVelocity.Z);
		//TDS::SetLinearAndAngularVelocity(*TDS::GetRigidBody(entityID), linearVelocityVec3, angularVelocityVec3);
	}

	void RigidBodyComponent::GetLinearAndAngularVelocity(Vector3& outLinearVelocity, Vector3& outAngularVelocity)
	{

	}

	void RigidBodyComponent::SetLinearVelocity(Vector3& inLinearVelocity)
	{

	}

	Vector3 RigidBodyComponent::GetLinearVelocity()
	{
		return Vector3(0.f, 0.f, 0.f);
	}

	void RigidBodyComponent::AddLinearVelocity(Vector3& inLinearVelocity)
	{

	}

	void RigidBodyComponent::AddLinearAndAngularVelocity(Vector3& inLinearVelocity, Vector3& inAngularVelocity)
	{

	}

	void RigidBodyComponent::SetAngularVelocity(Vector3& inAngularVelocity)
	{

	}

	Vector3 RigidBodyComponent::GetAngularVelocity()
	{
		return Vector3(0.f, 0.f, 0.f);
	}

	Vector3 RigidBodyComponent::GetPointVelocity(Vector3& inPoint)
	{
		return Vector3(0.f, 0.f, 0.f);
	}
	//void SetPositionRotationAndVelocity(Vector3& inPosition, Quat& inRotation, Vector3& inLinearVelocity, Vector3& inAngularVelocity);

	RigidBodyComponent::RigidBodyComponent(TDS::EntityID ID) : entityID (ID)
	{ }
}