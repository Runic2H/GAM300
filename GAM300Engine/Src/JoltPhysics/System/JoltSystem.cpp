#include "JoltPhysics/System/JoltSystem.h"

#include "Physics/PhysicsSystem.h"

namespace TDS
{
	PhysicsSystem* mPhysicsSystem;
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
				//JPH::BodyCreationSettings sphereSetting((new JPH::SphereShape(vSphere->GetRadius())), // -> this one need convert from TDS to JPH
				//										vSphere->GetCenter(), JPH::Quat::sIdentity(),
				//										_rigidbody->get_type(),
				//										Layers::MOVING);
				//JPH::BodyID sphereID = pBodies->CreateAndAddBody(sphereSetting, EActivation::Activate);
				// // At this pt, pBodies have a bodyID and a collision shape, ready to be simulate in physicsSystem::update
				//_rigidbody->SetBodyID(sphereID);
			}
			else if (GetBoxCollider(entities[i]) && _rigidbody->GetBodyID() == JPH::BodyID::cInvalidBodyID)
			{
				auto* vBox = GetBoxCollider(entities[i]);
				JPH::BoxShapeSettings boxSettings(vBox->GetSize());
				ShapeSettings::ShapeResult boxResult = boxSettings.Create();
				ShapeRefC boxShape = boxResult.Get();
				BodyCreationSettings boxSetting(boxShape, vBox->GetCenter(), JPH::Quat::sIdentity(), _rigidbody->get_type(), Layers::MOVING);
				Body* bodyID = pBodies->CreateBody(boxSetting);
				pBodies->AddBody(bodyID->GetID(), EActivation::Activate);
				_rigidbody->SetBodyID(bodyID->GetID());
			}
		}
	}
}
