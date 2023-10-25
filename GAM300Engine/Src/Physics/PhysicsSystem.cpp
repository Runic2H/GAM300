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



//for threadpool
#include <thread>
#include <cstdarg>

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h> //jolt physics system
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

namespace TDS
{
	const double PhysicsSystem::fixedDt = 0.0166666f;
	double PhysicsSystem::accumulatedTime = 0.0f;

	void PhysicsSystem::JoltPhysicsSystemInit()
	{
		// Register allocation hook
		RegisterDefaultAllocator();

		// Install callbacks
		Trace = TraceImpl;
		JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

			// Create a factory
			Factory::sInstance = new Factory();

		// Register all Jolt physics types
		RegisterTypes();

		// We need a temp allocator for temporary allocations during the physics update. We're
		// pre-allocating 10 MB to avoid having to do allocations during the physics update.
		// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
		// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
		// malloc / free.
		m_tempAllocator = std::make_unique<TempAllocatorImpl>(10 * 1024 * 1024);

		// We need a job system that will execute physics jobs on multiple threads. Typically
		// you would implement the JobSystem interface yourself and let Jolt Physics run on top
		// of your own job scheduler. JobSystemThreadPool is an example implementation.
		m_jobSystemThreadPool = std::make_unique<JobSystemThreadPool>(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);
		// Create mapping table from object layer to broadphase layer
		// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
		BPLayerInterfaceImpl broad_phase_layer_interface;

		// Create class that filters object vs broadphase layers
		// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
		ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;

		// Create class that filters object vs object layers
		// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
		ObjectLayerPairFilterImpl object_vs_object_layer_filter;

		m_physicsSystem = std::make_unique<JPH::PhysicsSystem>();
		m_physicsSystem->Init(	PhysicsSystem::cMaxBodies,
								PhysicsSystem::cNumBodyMutexes,
								PhysicsSystem::cMaxBodyPairs, 
								PhysicsSystem::cMaxContactConstraints, 
								broad_phase_layer_interface, 
								object_vs_broadphase_layer_filter, 
								object_vs_object_layer_filter);

		// A body activation listener gets notified when bodies activate and go to sleep
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		MyBodyActivationListener body_activation_listener;
		m_physicsSystem->SetBodyActivationListener(&body_activation_listener);

		// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		MyContactListener contact_listener;
		m_physicsSystem->SetContactListener(&contact_listener);

		// The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
		// variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)

		JPH::BodyInterface& body_interface = m_physicsSystem->GetBodyInterface();

		// Next we can create a rigid body to serve as the floor, we make a large box
		// Create the settings for the collision volume (the shape).
		// Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
		BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 1.0f, 100.0f));

		// Create the shape
		ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
		ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

		// Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
		BodyCreationSettings floor_settings(floor_shape, RVec3(0.0_r, -1.0_r, 0.0_r), JPH::Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);

		// Create the actual rigid body
		Body* floor = body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr

		// Add it to the world
		body_interface.AddBody(floor->GetID(), EActivation::DontActivate);

		// Now create a dynamic body to bounce on the floor
		// Note that this uses the shorthand version of creating and adding a body to the world
		BodyCreationSettings sphere_settings(new SphereShape(0.5f), RVec3(0.0_r, 2.0_r, 0.0_r), JPH::Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
		sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

		// Now you can interact with the dynamic body, in this case we're going to give it a velocity.
		// (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
		body_interface.SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, -5.0f, 0.0f));

		// Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision detection performance (it's pointless here because we only have 2 bodies).
		// You should definitely not call this every frame or when e.g. streaming in a new level section as it is an expensive operation.
		// Instead insert all new objects in batches instead of 1 at a time to keep the broad phase efficient.
		m_physicsSystem->OptimizeBroadPhase();
		std::cout << "successfully init Jolt Physics" << '\n';

	}
	
	void PhysicsSystem::JoltPhysicsSystemUpdate()
	{
		// Next step
		// Now we're ready to simulate the body, keep simulating until it goes to sleep
		uint step = 0;

		++step;

		// Output current position and velocity of the sphere
		JPH::BodyInterface& body_interface = m_physicsSystem->GetBodyInterface();
		RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
		JPH::Vec3 velocity = body_interface.GetLinearVelocity(sphere_id);
		std::cout << "Step " << step << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << std::endl;

		// If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
		const int cCollisionSteps = 1;

		// Step the world
		m_physicsSystem->Update(cDeltaTime, cCollisionSteps, m_tempAllocator.get(), m_jobSystemThreadPool.get());

	}

	void PhysicsSystem::PhysicsSystemInit()
	{
		PhysicsSystem JPH_pSystem;
		JPH_pSystem.JoltPhysicsSystemInit();
	}

	void PhysicsSystem::PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody)
	{
		//TDS_INFO(entities.size());
		// Physics loop
		//accumulatedTime += dt;
		//while (accumulatedTime >= TimeStep::GetFixedDeltaTime())
		//{
		//	for (int i = 0; i < entities.size(); ++i)
		//	{
		//		_rigidbody->setInverseMass(_rigidbody->GetMass());
		//		NewtonianPhysics(_transform[i], _rigidbody[i]);
		//	}
		//	accumulatedTime -= TimeStep::GetFixedDeltaTime();
		//}	
		PhysicsSystem JPH_pSystem;
		JPH_pSystem.JoltPhysicsSystemUpdate();
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

	//need to put this in a future destructor
	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	//body_interface.RemoveBody(sphere_id);

	//// Destroy the sphere. After this the sphere ID is no longer valid.
	//body_interface.DestroyBody(sphere_id);

	//// Remove and destroy the floor
	//body_interface.RemoveBody(floor->GetID());
	//body_interface.DestroyBody(floor->GetID());
	
}
