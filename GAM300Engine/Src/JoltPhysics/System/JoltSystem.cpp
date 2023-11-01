#include "JoltPhysics/System/JoltSystem.h"

#include "Logger/Logger.h"
#include "Physics/PhysicsSystem.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
//Will need to reformat to have a more flexible system

namespace TDS
{
//	// b_xxx -> bodycreationsetting xxx
//	// s_xxx -> xxx Shape setting
	void JoltSystem::Init()
	{
	}
	void JoltSystem::Update(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody)
	{
		// There should only be one collider for each entity
		JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
		for (int i = 0; i < entities.size(); ++i)
		{
			EMotionType vMotionType = JoltConversionUtils::ToEMotionType(_rigidbody->GetMotionType());
			// Add collider shape to body for Jolt Physics
			if (!_rigidbody->GetBodyID().IsInvalid() && vMotionType != pBodies->GetMotionType(JoltConversionUtils::ToBodyID(_rigidbody)))
			{
				TDS_INFO("Motion Type changed from {} to {}", (int)pBodies->GetMotionType(JoltConversionUtils::ToBodyID(_rigidbody)),(int)vMotionType);
				pBodies->SetMotionType(JoltConversionUtils::ToBodyID(_rigidbody), vMotionType, JPH::EActivation::DontActivate);
			}
			if (GetSphereCollider(entities[i]) && _rigidbody->GetBodyID().GetIndexAndSequenceNumber() == JPH::BodyID::cInvalidBodyID)
			{
				auto* vSphere = GetSphereCollider(entities[i]);
				JPH::SphereShapeSettings s_sphereSettings(vSphere->GetRadius());
				JPH::ShapeSettings::ShapeResult result = s_sphereSettings.Create(); 
				JPH::ShapeRefC sphereShape = result.Get(); // if error, high chance is how the shape is created, radius cannot be 0!
				// There should be a better way to get info for creation of body, potentially consdier SetUserData()?
				JPH::BodyCreationSettings b_SphereSetting;
				
				b_SphereSetting.mAllowDynamicOrKinematic = true;
				b_SphereSetting.mAngularDamping = _rigidbody->GetAngularDamping();
				b_SphereSetting.mLinearDamping = _rigidbody->GetLinearDamping();
				b_SphereSetting.mFriction = _rigidbody->GetFriction();
				b_SphereSetting.mRestitution = _rigidbody->GetRestitution();
				b_SphereSetting.mLinearVelocity = JoltConversionUtils::ToVec3(_rigidbody->GetLinearVel());
				b_SphereSetting.mAngularVelocity = JoltConversionUtils::ToVec3(_rigidbody->GetAngularVel());
				b_SphereSetting.mMassPropertiesOverride.mMass = _rigidbody->GetMass();
				b_SphereSetting.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
				b_SphereSetting.mAllowSleeping = false;
				b_SphereSetting.mPosition = JoltConversionUtils::ToVec3(_transform->GetPosition());
				b_SphereSetting.mRotation = JoltConversionUtils::ToQuat(_transform->GetRotation());
				b_SphereSetting.mObjectLayer = JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt());
				b_SphereSetting.mMotionType = vMotionType;
				b_SphereSetting.SetShape(sphereShape);
				
				JPH::BodyID sphereID = pBodies->CreateAndAddBody(b_SphereSetting, JPH::EActivation::Activate);
				TDS_INFO("Sphere Created!");
				
				JoltBodyID vJoltBodyID(sphereID.GetIndexAndSequenceNumber());
				_rigidbody->SetBodyID(vJoltBodyID);
			}

			else if (GetBoxCollider(entities[i]) && _rigidbody->GetBodyID().GetIndexAndSequenceNumber() == JPH::BodyID::cInvalidBodyID)
			{
				//JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
				auto* vBox = GetBoxCollider(entities[i]);
				JPH::Vec3 halfExtents = JoltConversionUtils::ToVec3(vBox->GetSize());
				halfExtents *= 0.5f;
				JPH::BoxShapeSettings s_boxSettings(halfExtents);
				JPH::ShapeSettings::ShapeResult result = s_boxSettings.Create();
				JPH::ShapeRefC boxShape = result.Get();
				JPH::BodyCreationSettings b_BoxSetting(boxShape,
														JoltConversionUtils::ToVec3(_transform->GetPosition()),
														JoltConversionUtils::ToQuat((_transform->GetRotation())),
														JPH::EMotionType(_rigidbody->GetMotionType()),
														JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt()));

				b_BoxSetting.mAllowDynamicOrKinematic = true;
				b_BoxSetting.mAngularDamping = _rigidbody->GetAngularDamping();
				b_BoxSetting.mLinearDamping = _rigidbody->GetLinearDamping();
				b_BoxSetting.mFriction = _rigidbody->GetFriction();
				b_BoxSetting.mRestitution = _rigidbody->GetRestitution();
				b_BoxSetting.mLinearVelocity = JoltConversionUtils::ToVec3(_rigidbody->GetLinearVel());
				b_BoxSetting.mAngularVelocity = JoltConversionUtils::ToVec3(_rigidbody->GetAngularVel());

				JPH::BodyID boxID = pBodies->CreateAndAddBody(b_BoxSetting, JPH::EActivation::Activate);
				TDS_INFO("Box Created!");
				JoltBodyID vJoltBodyID(boxID.GetIndexAndSequenceNumber());
				_rigidbody->SetBodyID(vJoltBodyID);
			}

			else if (GetCapsuleCollider(entities[i]) && _rigidbody->GetBodyID().GetIndexAndSequenceNumber() == JPH::BodyID::cInvalidBodyID)
			{
				//JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
				auto* vCapsule = GetCapsuleCollider(entities[i]);
				JPH::CapsuleShapeSettings s_capsuleSettings(vCapsule->GetHeight(), vCapsule->GetRadius());
				JPH::ShapeSettings::ShapeResult result = s_capsuleSettings.Create();
				JPH::ShapeRefC capsuleShape = result.Get();
				JPH::BodyCreationSettings b_CapsuleSetting(capsuleShape, 
															JoltConversionUtils::ToVec3(_transform->GetPosition()),
															JoltConversionUtils::ToQuat((_transform->GetRotation())),
															JPH::EMotionType(_rigidbody->GetMotionType()),
															JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt()));

				b_CapsuleSetting.mAllowDynamicOrKinematic = true;
				b_CapsuleSetting.mAngularDamping = _rigidbody->GetAngularDamping();
				b_CapsuleSetting.mLinearDamping = _rigidbody->GetLinearDamping();
				b_CapsuleSetting.mFriction = _rigidbody->GetFriction();
				b_CapsuleSetting.mRestitution = _rigidbody->GetRestitution();
				b_CapsuleSetting.mLinearVelocity = JoltConversionUtils::ToVec3(_rigidbody->GetLinearVel());
				b_CapsuleSetting.mAngularVelocity = JoltConversionUtils::ToVec3(_rigidbody->GetAngularVel());

				JPH::BodyID capsuleID = pBodies->CreateAndAddBody(b_CapsuleSetting, JPH::EActivation::Activate);
				TDS_INFO("Capsule Created!");
				JoltBodyID vJoltBodyID(capsuleID.GetIndexAndSequenceNumber());
				_rigidbody->SetBodyID(vJoltBodyID);
			}
		}
	}
}
