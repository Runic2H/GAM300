#include "JoltPhysics/System/JoltSystem.h"

#include "Physics/PhysicsSystem.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>

namespace TDS
{
	// b_xxx -> bodycreationsetting xxx
	// s_xxx -> xxx Shape setting
	void JoltSystem::Init()
	{
	}
	void JoltSystem::Update(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody)
	{
		// There should only be one collider for each entity
		JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
		for (int i = 0; i < entities.size(); ++i)
		{
			//if (_rigidbody->GetBodyID() != JPH::BodyID::cInvalidBodyID)
			//{
			//	if (pBodies->GetMotionType(JPH::BodyID(_rigidbody->GetBodyID())) != JPH::EMotionType(_rigidbody->GetMotionTypeInt()))
			//	{
			//		BodyID bodyID = JPH::BodyID(_rigidbody->GetBodyID());
			//		//TDS_INFO("Motion Type change from {} to {}", pBodies->GetMotionType(bodyID), JPH::EMotionType(_rigidbody->GetMotionType()));
			//		pBodies->SetMotionType(bodyID, JPH::EMotionType(_rigidbody->GetMotionTypeInt()), JPH::EActivation::Activate);
			//		std::cout << "motion type change" << '\n';
			//	}
			//}
			// Add collider shape to body for Jolt Physics
			if (GetSphereCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				//JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
				auto* vSphere = GetSphereCollider(entities[i]);
				JPH::SphereShapeSettings s_sphereSettings(vSphere->GetRadius());
				JPH::ShapeSettings::ShapeResult result = s_sphereSettings.Create(); 
				JPH::ShapeRefC sphereShape = result.Get(); // if error, high chance is how the shape is created, radius cannot be 0!
				// There should be a better way to get info for creation of body, potentially consdier SetUserData()?
				JPH::BodyCreationSettings b_SphereSetting(sphereShape, 
															JoltConversionUtils::ToVec3(_transform->GetPosition()),
															JoltConversionUtils::ToQuat((_transform->GetRotation())),
															JPH::EMotionType(_rigidbody->GetMotionType()), 
															JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt()));

				JPH::BodyID sphereID = pBodies->CreateAndAddBody(b_SphereSetting, JPH::EActivation::Activate);
				pBodies->GetMotionType(sphereID);
				TDS_INFO("Sphere Created!");
				_rigidbody->SetBodyID(sphereID.GetIndex());
			}

			else if (GetBoxCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
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

				JPH::BodyID boxID = pBodies->CreateAndAddBody(b_BoxSetting, JPH::EActivation::Activate);
				TDS_INFO("Box Created!");
				_rigidbody->SetBodyID(boxID.GetIndex());
			}

			else if (GetCapsuleCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
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

				JPH::BodyID capsuleID = pBodies->CreateAndAddBody(b_CapsuleSetting, JPH::EActivation::Activate);
				TDS_INFO("Capsule Created!");
				_rigidbody->SetBodyID(capsuleID.GetIndex());
			}
		}
	}
}
