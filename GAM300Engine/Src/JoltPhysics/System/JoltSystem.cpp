#include "JoltPhysics/System/JoltSystem.h"

#include "Physics/PhysicsSystem.h"

namespace TDS
{
	PhysicsSystem* mPhysicsSystem;
	// b_xxx -> bodycreationsetting xxx
	// s_xxx -> xxx Shape setting
	void JoltSystem::Init()
	{
	}
	void JoltSystem::Update(const float dt, const std::vector<EntityID>& entities, RigidBody* _rigidbody)
	{
		// There should only be one collider for each entity
		JPH::PhysicsSystem* pSystem = mPhysicsSystem->GetPhysicsSystem();
		JPH::BodyInterface* pBodies = &pSystem->GetBodyInterface(); // use pBodies to set velocity, mass etc.
		for (int i = 0; i < entities.size(); ++i)
		{
			if (GetSphereCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				auto* vSphere = GetSphereCollider(entities[i]);
				JPH::SphereShapeSettings s_sphereSettings(vSphere->GetRadius());
				JPH::ShapeSettings::ShapeResult result = s_sphereSettings.Create(); // can check result for HasError()/ GetError()
				JPH::ShapeRefC sphereShape = result.Get();
				// Argument need to change with IMGUI settings
				JPH::BodyCreationSettings b_SphereSetting(sphereShape, RVec3(0.0, -1.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);
				JPH::BodyID sphereID = pBodies->CreateAndAddBody(b_SphereSetting, JPH::EActivation::Activate);
				_rigidbody->SetBodyID(sphereID.GetIndex());
			}

			else if (GetBoxCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				//auto* vBox = GetBoxCollider(entities[i]);
				//JPH::BoxShapeSettings boxSettings(vBox->GetSize());
				//ShapeSettings::ShapeResult boxResult = boxSettings.Create();
				//ShapeRefC boxShape = boxResult.Get();
				//BodyCreationSettings boxSetting(boxShape, vBox->GetCenter(), JPH::Quat::sIdentity(), _rigidbody->get_type(), Layers::MOVING);
				//Body* bodyID = pBodies->CreateBody(boxSetting);
				//pBodies->AddBody(bodyID->GetID(), EActivation::Activate);
				//_rigidbody->SetBodyID(bodyID->GetID());
			}
		}
	}
}
