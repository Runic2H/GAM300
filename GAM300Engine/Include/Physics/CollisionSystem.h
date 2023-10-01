/*!*****************************************************************************
 * \file          CollisionSystem.h
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         The system that check and handle collision.
 *******************************************************************************/
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ecs/ecs.h"
#include "components/collider.h"
#include "components/transform.h"
#include "components/rigidBody.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API CollisionSystem
	{
	public:
		/*!*************************************************************************
		 * Collision System Init and Update (Will be used by the ECS)
		 ***************************************************************************/
		static void CollisionSystemInit();
		static void CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider);
		
	private:
		/*!*************************************************************************
		 * Sphere to Sphere Collision Check
		 ***************************************************************************/
		static bool SphereSphereCollision(Transform& trans1, RigidBody& body1, Collider& collider1, Transform& trans2, RigidBody& body2, Collider& collider2);
		/*!*************************************************************************
		 * Sphere to Sphere Collision Response
		 ***************************************************************************/
		static void SphereSphereResolution(Transform& trans1, RigidBody& body1, Transform& trans2, RigidBody& body2);

	};
}


#endif // !COLLISIONSYSTEM_H
