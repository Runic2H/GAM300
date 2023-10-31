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
	void JoltSystem::Update(const float dt, const std::vector<EntityID>& entities, RigidBody* _rigidbody)
	{
		// There should only be one collider for each entity
		for (int i = 0; i < entities.size(); ++i)
		{
			if (GetSphereCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
				auto* vSphere = GetSphereCollider(entities[i]);
				JPH::SphereShapeSettings s_sphereSettings(vSphere->GetRadius());
				JPH::ShapeSettings::ShapeResult result = s_sphereSettings.Create(); 
				JPH::ShapeRefC sphereShape = result.Get(); // if error, high chance is how the shape is created, radius cannot be 0!
				// Argument need to change with IMGUI settings
				JPH::BodyCreationSettings b_SphereSetting(sphereShape, RVec3(0.0, -1.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);
				JPH::BodyID sphereID = pBodies->CreateAndAddBody(b_SphereSetting, JPH::EActivation::Activate);
				TDS_INFO("Sphere Created!");
				_rigidbody->SetBodyID(sphereID.GetIndex());
			}

			else if (GetBoxCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
				auto* vBox = GetBoxCollider(entities[i]);
				JPH::Vec3 halfExtents (vBox->GetSize().x, vBox->GetSize().y, vBox->GetSize().z);
				halfExtents *= 0.5f;
				JPH::BoxShapeSettings s_boxSettings(halfExtents);
				JPH::ShapeSettings::ShapeResult result = s_boxSettings.Create();
				JPH::ShapeRefC boxShape = result.Get();
				JPH::BodyCreationSettings b_BoxSetting(boxShape, RVec3(0.0, -1.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);
				JPH::BodyID boxID = pBodies->CreateAndAddBody(b_BoxSetting, JPH::EActivation::Activate);
				TDS_INFO("Box Created!");
				_rigidbody->SetBodyID(boxID.GetIndex());
			}

			else if (GetCapsuleCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				JPH::BodyInterface* pBodies = &PhysicsSystem::m_pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
				auto* vCapsule = GetCapsuleCollider(entities[i]);
				JPH::CapsuleShapeSettings s_capsuleSettings(vCapsule->GetHeight(), vCapsule->GetRadius());
				JPH::ShapeSettings::ShapeResult result = s_capsuleSettings.Create();
				JPH::ShapeRefC capsuleShape = result.Get();
				JPH::BodyCreationSettings b_CapsuleSetting(capsuleShape, RVec3(0.0, -1.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);
				JPH::BodyID capsuleID = pBodies->CreateAndAddBody(b_CapsuleSetting, JPH::EActivation::Activate);
				TDS_INFO("Capsule Created!");
				_rigidbody->SetBodyID(capsuleID.GetIndex());
			}
		}
	}
}
