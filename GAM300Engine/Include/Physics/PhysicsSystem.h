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
#include "Logger/Logger.h"

 // Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>


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

		void JoltPhysicsSystemInit();

	private:
		static const double fixedDt;
		static double accumulatedTime;
		std::unique_ptr<JPH::PhysicsSystem> m_physicsSystem;
	};
}



#endif // !PHYSICSSYSTEM_H
