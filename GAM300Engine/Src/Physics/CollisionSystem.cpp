/*!*****************************************************************************
 * \file          CollisionSystem.cpp
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Implementation of the collision system.
 *******************************************************************************/
#include "Physics/CollisionSystem.h"

namespace TDS
{
	void CollisionSystem::CollisionSystemInit()
	{
	}
	
	void CollisionSystem::CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider)
	{
		for (int i = 0; i < entities.size(); ++i)
		{
			for (int j = 0; j < entities.size(); ++j)
			{
				if (i == j)
					continue;
				if (_collider[i].GetColliderType() == Collider::ColliderType::CIRCLE && _collider[j].GetColliderType() == Collider::ColliderType::CIRCLE)
				{
					if (SphereSphereCollision(_transform[i], _rigidbody[i], _collider[i],_transform[j], _rigidbody[j], _collider[j]))
					{
						SphereSphereResolution(_transform[i], _rigidbody[i], _transform[j], _rigidbody[j]);
					
					}
				}
				else if (_collider[i].GetColliderType() == Collider::ColliderType::CIRCLE && _collider[j].GetColliderType() == Collider::ColliderType::RECTANGLE ||
					_collider[i].GetColliderType() == Collider::ColliderType::RECTANGLE && _collider[j].GetColliderType() == Collider::ColliderType::CIRCLE)
				{
					// TODO: Implement Circle-Rectangle collision
				}
			}
		}
	}


	/*Helper Function*/
	bool CollisionSystem::SphereSphereCollision(Transform& trans1, RigidBody& body1, Collider& collider1, Transform& trans2, RigidBody& body2, Collider& collider2)
	{
		// get the distance between the two objects
		float distance = (trans1.GetPosition() - trans2.GetPosition()).magnitude();
		// if the distance is less than the sum of the two radii, they are colliding
		if (distance < collider1.GetRadius() + collider2.GetRadius())
		{
			return true;
		}
		return false;
	}

	void CollisionSystem::SphereSphereResolution(Transform& trans1, RigidBody& body1, Transform& trans2, RigidBody& body2)
	{
		// get the direction of both objects, reflect them and multiply back into the forces
		Vec3 Dir1 = body1.GetDirection();
		Vec3 Dir2 = body2.GetDirection();
		Dir1 = Dir1 * -1;
		Dir2 = Dir2 * -1;
		body1.SetDirection(Dir1);
		body2.SetDirection(Dir2);
		body1.SetInputForce(body1.GetInputForce() * -1);
		body2.SetInputForce(body2.GetInputForce() * -1);
	}

	
}

