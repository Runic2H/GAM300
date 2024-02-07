#include "Physics/Interface/PhysicsInterface.h"
#include "Physics/PhysicsSystem.h"

namespace TDS
{
	using namespace JoltToTDS;
	void MoveKinematic(RigidBody& rb, Vec3& inTargetPosition, Quat& inTargetRotation, float inDeltaTime)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->MoveKinematic(ToBodyID(rb), ToVec3(inTargetPosition), ToQuat(inTargetRotation), inDeltaTime);
	}
	void SetLinearAndAngularVelocity(RigidBody& rb, Vec3& inLinearVelocity, Vec3& inAngularVelocity)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetLinearAndAngularVelocity(ToBodyID(rb), ToVec3(inLinearVelocity), ToVec3(inAngularVelocity));
	}
	void GetLinearAndAngularVelocity(RigidBody& rb, Vec3& outLinearVelocity, Vec3& outAngularVelocity)
	{
		JPH::Vec3 OutLinearJPH;
		JPH::Vec3 OutAngularJPH;
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->GetLinearAndAngularVelocity(ToBodyID(rb), OutLinearJPH, OutAngularJPH);
		
		outLinearVelocity = ToVec3(OutLinearJPH);
		outAngularVelocity = ToVec3(OutAngularJPH);
	}
	void SetLinearVelocity(RigidBody& rb, Vec3& velocity)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetLinearVelocity(ToBodyID(rb), ToVec3(velocity));
	}
	Vec3 GetLinearVelocity(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Vec3 OutLinearJPH = pBodyInterface->GetLinearVelocity(ToBodyID(rb));
	
		return ToVec3(OutLinearJPH);
	}
	void AddLinearVelocity(RigidBody& rb, Vec3& inLinearVelocity)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddLinearVelocity(ToBodyID(rb), ToVec3(inLinearVelocity));
	}
	void AddLinearAndAngularVelocity(RigidBody& rb, Vec3& inLinearVelocity, Vec3& inAngularVelocity)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddLinearAndAngularVelocity(ToBodyID(rb), ToVec3(inLinearVelocity), ToVec3(inAngularVelocity));
	}
	void SetAngularVelocity(RigidBody& rb, Vec3& inAngularVelocity)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetAngularVelocity(ToBodyID(rb), ToVec3(inAngularVelocity));
	}
	Vec3 GetAngularVelocity(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Vec3 OutAngularJPH = pBodyInterface->GetAngularVelocity(ToBodyID(rb));
		return ToVec3(OutAngularJPH);
	}
	Vec3 GetPointVelocity(RigidBody& rb, Vec3& inPoint)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Vec3 OutPointJPH = pBodyInterface->GetPointVelocity(ToBodyID(rb), ToVec3(inPoint));
		return ToVec3(OutPointJPH);
	}
	void SetPositionRotationAndVelocity(RigidBody& rb, Vec3& inPosition, Quat& inRotation, Vec3& inLinearVelocity, Vec3& inAngularVelocity)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetPositionRotationAndVelocity(ToBodyID(rb), ToVec3(inPosition), ToQuat(inRotation), ToVec3(inLinearVelocity), ToVec3(inAngularVelocity));
	}
	Mat4 GetInverseInertia(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Mat44 OutInverseInertiaJPH = pBodyInterface->GetInverseInertia(ToBodyID(rb));
		return ToMat4(OutInverseInertiaJPH);
	}
	void SetPositionAndRotation(RigidBody& rb, Vec3& inPosition, Quat& inRotation, bool inActivate /*true = Activate, false = DontActivate*/)
	{
		EActivation activate;
		inActivate == true ? activate = EActivation::Activate : activate = EActivation::DontActivate;
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetPositionAndRotation(ToBodyID(rb), ToVec3(inPosition), ToQuat(inRotation), activate);
	}
	void SetPositionAndRotationWhenChanged(RigidBody& rb, Vec3& inPosition, Quat& inRotation, bool inActivate /*true = Activate, false = DontActivate*/)
	{
		EActivation activate;
		inActivate == true ? activate = EActivation::Activate : activate = EActivation::DontActivate;
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetPositionAndRotationWhenChanged(ToBodyID(rb), ToVec3(inPosition), ToQuat(inRotation), activate);
	}
	void GetPositionAndRotation(RigidBody& rb, Vec3& outPosition, Quat& outRotation)
	{
		JPH::Vec3 OutPositionJPH;
		JPH::Quat OutRotationJPH;
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->GetPositionAndRotation(ToBodyID(rb), OutPositionJPH, OutRotationJPH);
		outPosition = ToVec3(OutPositionJPH);
		outRotation = ToQuat(OutRotationJPH);
	}
	void SetPosition(RigidBody& rb, Vec3& inPosition, bool inActivate)
	{
		EActivation activate;
		inActivate == true ? activate = EActivation::Activate : activate = EActivation::DontActivate;
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetPosition(ToBodyID(rb), ToVec3(inPosition), activate);
	}
	Vec3 GetPosition(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Vec3 OutPositionJPH = pBodyInterface->GetPosition(ToBodyID(rb));
		return ToVec3(OutPositionJPH);
	}
	Vec3 GetCenterOfMassPosition(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Vec3 OutCenterOfMassPositionJPH = pBodyInterface->GetCenterOfMassPosition(ToBodyID(rb));
		return ToVec3(OutCenterOfMassPositionJPH);
	}
	void SetRotation(RigidBody& rb, Quat& inRotation, bool inActivate)
	{
		EActivation activate;
		inActivate == true ? activate = EActivation::Activate : activate = EActivation::DontActivate;
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetRotation(ToBodyID(rb), ToQuat(inRotation), activate);
	}
	Quat GetRotation(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Quat OutRotationJPH = pBodyInterface->GetRotation(ToBodyID(rb));
		return ToQuat(OutRotationJPH);
	}
	Mat4 GetWorldTransform(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Mat44 OutWorldTransformJPH = pBodyInterface->GetWorldTransform(ToBodyID(rb));
		return ToMat4(OutWorldTransformJPH);
	}
	Mat4 GetCenterOfMassTransform(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		JPH::Mat44 OutCenterOfMassTransformJPH = pBodyInterface->GetCenterOfMassTransform(ToBodyID(rb));
		return ToMat4(OutCenterOfMassTransformJPH);
	}
	void AddForce(RigidBody& rb, Vec3& inForce)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddForce(ToBodyID(rb), ToVec3(inForce));
	}
	void AddForce(RigidBody& rb, Vec3& inForce, Vec3& inPoint)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddForce(ToBodyID(rb), ToVec3(inForce), ToVec3(inPoint));
	}
	void AddTorque(RigidBody& rb, Vec3& inTorque)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddTorque(ToBodyID(rb), ToVec3(inTorque));
	}
	void AddForceAndTorque(RigidBody& rb, Vec3& inForce, Vec3& inTorque)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddForceAndTorque(ToBodyID(rb), ToVec3(inForce), ToVec3(inTorque));
	}
	void AddImpulse(RigidBody& rb, Vec3& inImpulse)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddImpulse(ToBodyID(rb), ToVec3(inImpulse));
	}
	void AddImpulse(RigidBody& rb, Vec3& inImpulse, Vec3& inPoint)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddImpulse(ToBodyID(rb), ToVec3(inImpulse), ToVec3(inPoint));
	}
	void AddAngularImpulse(RigidBody& rb, Vec3& inAngularImpulse)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->AddAngularImpulse(ToBodyID(rb), ToVec3(inAngularImpulse));
	}
	void SetRestitution(RigidBody& rb, float inRestitution)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetRestitution(ToBodyID(rb), inRestitution);
	}
	float GetRestitution(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		return pBodyInterface->GetRestitution(ToBodyID(rb));
	}
	void SetFriction(RigidBody& rb, float inFriction)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetFriction(ToBodyID(rb), inFriction);
	}
	float GetFriction(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		return pBodyInterface->GetFriction(ToBodyID(rb));
	}
	void SetGravityFactor(RigidBody& rb, float inGravityFactor)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		pBodyInterface->SetGravityFactor(ToBodyID(rb), inGravityFactor);
	}
	float GetGravityFactor(RigidBody& rb)
	{
		JPH::BodyInterface* pBodyInterface = &PhysicsSystem::m_pSystem->GetBodyInterface();
		return pBodyInterface->GetGravityFactor(ToBodyID(rb));
	}
}

