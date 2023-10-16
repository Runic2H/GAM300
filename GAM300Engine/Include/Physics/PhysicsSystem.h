/*!*****************************************************************************
 * \file          PhysicsSystem.h
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         The system that handles physics.
 *******************************************************************************/

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ecs/ecs.h"
#include "components/rigidBody.h"
#include "components/transform.h"
#include "dotnet/ImportExport.h"
#include "Timestep/Timestep.h"

// X = moving left, right
// Y = moving up, down
// Z = moving forward, backward

namespace TDS
{
	class DLL_API PhysicsSystem
	{
	public:
		/*!*************************************************************************
		 * Physics System Init and Update (Will be used by the ECS)
		 ***************************************************************************/
		static void PhysicsSystemInit();
		static void PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody);

	private:
		/*!*************************************************************************
		 * Calculate the total force acting on the object.
		 ***************************************************************************/
		static Vec3 CalculateTotalForce(RigidBody& _collider);
		/*!*************************************************************************
		 * With the total force, calculate the new position with Newton's law
		 ***************************************************************************/
		static void NewtonianPhysics(Transform& _transform, RigidBody& _rigidbody);
		/*!*************************************************************************
		 * Set the object direction based on the force
		 ***************************************************************************/
		static void SettingObjectDirection(Vec3& totalForce, RigidBody& _rigidbody);
	private:
		static const double fixedDt;
		static double accumulatedTime;
	};
}



#endif // !PHYSICSSYSTEM_H
