/*!*****************************************************************************
 * \file          PhysicsSystem.cpp
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Implementation of the physics system.
 *******************************************************************************/
#include "Physics/PhysicsSystem.h"
namespace TDS
{
	const double PhysicsSystem::fixedDt = 0.0166666f;
	double PhysicsSystem::accumulatedTime = 0.0f;
		
	void PhysicsSystem::PhysicsSystemInit()
	{
	}

	void PhysicsSystem::PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody)
	{
		//TDS_INFO(entities.size());
		// Physics loop
		accumulatedTime += dt;
		while (accumulatedTime >= TimeStep::GetFixedDeltaTime())
		{
			for (int i = 0; i < entities.size(); ++i)
			{
				_rigidbody->setInverseMass(_rigidbody->GetMass());
				NewtonianPhysics(_transform[i], _rigidbody[i]);
			}
			accumulatedTime -= TimeStep::GetFixedDeltaTime();
		}
		
	}

	Vec3 PhysicsSystem::CalculateTotalForce(RigidBody& _rigidbody)
	{
		Vec3 totalForce		= Vec3(0.0f);
		totalForce			+= _rigidbody.GetInputForce();
		totalForce.y		+= (-_rigidbody.GetGravity() * _rigidbody.GetMass());
		_rigidbody.SetNormalizedForce(totalForce.normalize());
		return totalForce;
	}

	void PhysicsSystem::SettingObjectDirection(Vec3& totalForce, RigidBody& _rigidbody)
	{
		Vec3 direction = Vec3(0.0f);
		// If totalForce.axis > 0, direction.axis = 1, else if totalForce.axis < 0, direction.axis = -1, else direction.axis = 0
		direction.x = (totalForce.x > 0.0f) ? 1.0f : (totalForce.x < 0.0f) ? -1.0f : 0.0f; 
		direction.y = (totalForce.y > 0.0f) ? 1.0f : (totalForce.y < 0.0f) ? -1.0f : 0.0f;
		direction.z = (totalForce.z > 0.0f) ? 1.0f : (totalForce.z < 0.0f) ? -1.0f : 0.0f;
		_rigidbody.SetDirection(direction);
	}

	void PhysicsSystem::NewtonianPhysics(Transform& _transform, RigidBody& _rigidbody)
	{
		Vec3 totalForce = CalculateTotalForce(_rigidbody);
		SettingObjectDirection(totalForce, _rigidbody);

		Vec3 acceleration	= totalForce * _rigidbody.GetInverseMass();
		_rigidbody.SetAcceleration(acceleration);
		
		Vec3 velocity		= _rigidbody.GetLinearVel();
		velocity += acceleration * TimeStep::GetFixedDeltaTime();
		_rigidbody.SetLinearVel(velocity);
		
		Vec3 position		= _transform.GetPosition();
		position			+= velocity * TimeStep::GetFixedDeltaTime();
		_transform.SetPosition(position);
		_rigidbody.SetNextPosition(position);
	}

	
}
