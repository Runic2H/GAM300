#include "JoltPhysics/System/JoltSystem.h"

#include "Physics/PhysicsSystem.h"

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
				PhysicsSystem::m_pSystem->GetBodyActivationListener();
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
