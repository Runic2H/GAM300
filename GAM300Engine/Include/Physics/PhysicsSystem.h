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
#include "components/boxCollider.h"
#include "components/sphereCollider.h"
#include "components/capsuleCollider.h"
#include "components/transform.h"
#include "dotnet/ImportExport.h"
#include "Timestep/Timestep.h"
#include "Logger/Logger.h"
#include "Physics/JPHLayers.h"


#include "JoltPhysics/System/JoltCore.h"
#include "JoltPhysics/Utils/JoltConversionUtils.h"

 // Jolt includes
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>


JPH_SUPPRESS_WARNINGS

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

		//std::unique_ptr<JPH::PhysicsSystem>& getPhysicsSystem() { return m_pSystem; }
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

		void JPH_SystemShutdown();

		static void JPH_SystemUpdate(Transform* _transform, RigidBody* _rigidbody);
		static void JPH_CreateBodyID(const EntityID& entities, Transform* _transform, RigidBody* _rigidbody);

	private:
		// TDS Physics System
		static const double fixedDt;
		static double accumulatedTime;
		//PhysicsSystem* pSystem_ptr;

	
	private:
		// Jolt Physics Global Settings
		static std::unique_ptr<JPH::PhysicsSystem>			m_pSystem;
		static std::unique_ptr<JPH::TempAllocatorImpl>		m_pTempAllocator;

		static BPLayerInterfaceImpl							broad_phase_layer_interface;
		static ObjectVsBroadPhaseLayerFilterImpl			object_vs_broadphase_layer_filter;
		static ObjectLayerPairFilterImpl					object_vs_object_layer_filter;

		unsigned int								m_stepNumber = 0;
	};

}



#endif // !PHYSICSSYSTEM_H
