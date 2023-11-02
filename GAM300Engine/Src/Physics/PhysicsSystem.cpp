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
	/*!*************************************************************************
	 * Static variables
	 ***************************************************************************/
	const double								PhysicsSystem::fixedDt = 0.0166666f;
	double										PhysicsSystem::accumulatedTime = 0.0f;
	std::unique_ptr<JPH::PhysicsSystem>			PhysicsSystem::m_pSystem;
	std::unique_ptr<JPH::TempAllocatorImpl>		PhysicsSystem::m_pTempAllocator;

	BPLayerInterfaceImpl						PhysicsSystem::broad_phase_layer_interface;
	ObjectVsBroadPhaseLayerFilterImpl			PhysicsSystem::object_vs_broadphase_layer_filter;
	ObjectLayerPairFilterImpl					PhysicsSystem::object_vs_object_layer_filter;
	/*!*************************************************************************
	 * Configuration
	 ***************************************************************************/
	const unsigned int cMaxBodies = 10240;				// Maximum number of bodies in the physics system
	const unsigned int cNumBodyMutexes = 0;				// Autodetect
	const unsigned int cMaxBodyPairs = 65536;			// Max amount of body pair for broadphrase detection
	const unsigned int cMaxContactConstraints = 20480;	// Maximum number of contact constraints


	void PhysicsSystem::PhysicsSystemInit()
	{
		// Initialize the Jolt Core
		JoltCore::Init();
		// We need a temp allocator for temporary allocations during the physics update. We're
		// pre-allocating 10 MB to avoid having to do allocations during the physics update.
		// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
		// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
		// malloc / free.
		m_pTempAllocator = std::make_unique<TempAllocatorImpl>(10 * 1024 * 1024);

		m_pSystem = std::make_unique<JPH::PhysicsSystem>();
		m_pSystem->Init(cMaxBodies,
			cNumBodyMutexes,
			cMaxBodyPairs,
			cMaxContactConstraints,
			broad_phase_layer_interface,
			object_vs_broadphase_layer_filter,
			object_vs_object_layer_filter);

		// A body activation listener gets notified when bodies activate and go to sleep
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		MyBodyActivationListener body_activation_listener;
		m_pSystem->SetBodyActivationListener(&body_activation_listener);

		// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		MyContactListener contact_listener;
		m_pSystem->SetContactListener(&contact_listener);

		// The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
		// variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
		 /*{
			JPH::BodyInterface* pBodies = &m_pSystem->GetBodyInterface();
			//JPH::BodyInterface& body_interface = m_pSystem->GetBodyInterface();
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
			//Body* floor = mBodyInterface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr
			Body* floor = pBodies->CreateBody(floor_settings);// Note that if we run out of bodies this can return nullptr
			// Add it to the world
			pBodies->AddBody(floor->GetID(), EActivation::DontActivate);
		}*/
		// Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision detection performance (it's pointless here because we only have 2 bodies).
		// You should definitely not call this every frame or when e.g. streaming in a new level section as it is an expensive operation.
		// Instead insert all new objects in batches instead of 1 at a time to keep the broad phase efficient.
		m_pSystem->OptimizeBroadPhase();

		std::cout << "successfully init Jolt Physics" << '\n';
	}

	void PhysicsSystem::PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody)
	{
		//TDS_INFO(entities.size());
		// Physics loop
		accumulatedTime += dt;
		//while (accumulatedTime >= TimeStep::GetFixedDeltaTime())
		//{
		//	for (int i = 0; i < entities.size(); ++i)
		//	{
		//		_rigidbody->setInverseMass(_rigidbody->GetMass());
		//		NewtonianPhysics(_transform[i], _rigidbody[i]);
		//	}
		//	accumulatedTime -= TimeStep::GetFixedDeltaTime();
		//}			
		 while (accumulatedTime >= TimeStep::GetFixedDeltaTime())
		{
			for (int i = 0; i < entities.size(); ++i)
			{
				if (_rigidbody->GetBodyID().IsInvalid())
				{
					JPH_CreateBodyID(entities[i], &_transform[i], &_rigidbody[i]);
				}
				// JPH physics simulation
				m_pSystem->Update(TimeStep::GetFixedDeltaTime(), 1, m_pTempAllocator.get(), JoltCore::s_pJobSystem.get());
				// Update back to the ECS
				JPH_SystemUpdate(&_transform[i], &_rigidbody[i]);
			}
			accumulatedTime -= TimeStep::GetFixedDeltaTime();
		}	
		
	}
	void PhysicsSystem::JPH_SystemUpdate(Transform* _transform, RigidBody* _rigidbody)
	{
		JPH::BodyID JPHBodyID = JoltToTDS::ToBodyID(_rigidbody);
		JPH::BodyInterface* pBodies = &m_pSystem->GetBodyInterface();
		_transform->SetPosition(JoltToTDS::ToVec3(pBodies->GetPosition(JPHBodyID)));
		_transform->SetRotation(JoltToTDS::ToVec3(pBodies->GetRotation(JPHBodyID).GetXYZ()));
		_rigidbody->SetLinearVel(JoltToTDS::ToVec3(pBodies->GetLinearVelocity(JPHBodyID)));
		_rigidbody->SetAngularVel(JoltToTDS::ToVec3(pBodies->GetAngularVelocity(JPHBodyID)));
		//pBodies->GetWorldTransform
	}
	void PhysicsSystem::JPH_SystemShutdown()
	{
		m_pTempAllocator = nullptr;
		m_pSystem = nullptr;
	}

	void PhysicsSystem::JPH_CreateBodyID(const EntityID& _entityID, Transform* _transform, RigidBody* _rigidbody)
	{
		EMotionType vMotionType = JoltToTDS::ToEMotionType(_rigidbody->GetMotionType());
		if (GetSphereCollider(_entityID))
		{
			SphereCollider* vSphere = GetSphereCollider(_entityID);
			JPH::SphereShapeSettings s_sphereSettings(vSphere->GetRadius());
			JPH::ShapeSettings::ShapeResult result = s_sphereSettings.Create();
			JPH::ShapeRefC sphereShape = result.Get(); // if error, high chance is how the shape is created, radius cannot be 0!
			JPH::BodyCreationSettings b_SphereSetting
			(
				sphereShape,
				JoltToTDS::ToVec3(_transform->GetPosition()),
				JoltToTDS::ToQuat((_transform->GetRotation())),
				vMotionType,
				JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt())
			);
			b_SphereSetting.mFriction = _rigidbody->GetFriction();
			b_SphereSetting.mRestitution = _rigidbody->GetRestitution();
			b_SphereSetting.mLinearVelocity = JoltToTDS::ToVec3(_rigidbody->GetLinearVel());
			b_SphereSetting.mAngularVelocity = JoltToTDS::ToVec3(_rigidbody->GetAngularVel());
			
			JPH::BodyID sphereID = m_pSystem->GetBodyInterface().CreateAndAddBody(b_SphereSetting, JPH::EActivation::Activate);
			JoltBodyID vJoltBodyID(sphereID.GetIndexAndSequenceNumber());
			TDS_INFO("Sphere Created!");
			_rigidbody->SetBodyID(vJoltBodyID);	
		}
		else if (GetBoxCollider(_entityID))
		{
			BoxCollider* vBox = GetBoxCollider(_entityID);
			JPH::Vec3 halfExtents = JoltToTDS::ToVec3(vBox->GetSize());
			halfExtents *= 0.5f;
			JPH::BoxShapeSettings s_boxSettings(halfExtents);
			JPH::ShapeSettings::ShapeResult result = s_boxSettings.Create();
			JPH::ShapeRefC boxShape = result.Get();
			JPH::BodyCreationSettings b_BoxSetting
				(
					boxShape,
					JoltToTDS::ToVec3(_transform->GetPosition()),
					JoltToTDS::ToQuat((_transform->GetRotation())),
					vMotionType,
					JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt())
				);
			b_BoxSetting.mFriction = _rigidbody->GetFriction();
			b_BoxSetting.mRestitution = _rigidbody->GetRestitution();
			b_BoxSetting.mLinearVelocity = JoltToTDS::ToVec3(_rigidbody->GetLinearVel());
			b_BoxSetting.mAngularVelocity = JoltToTDS::ToVec3(_rigidbody->GetAngularVel());

			JPH::BodyID boxID = m_pSystem->GetBodyInterface().CreateAndAddBody(b_BoxSetting, JPH::EActivation::Activate);
			JoltBodyID vJoltBodyID(boxID.GetIndexAndSequenceNumber());
			TDS_INFO("Box Created!");
			_rigidbody->SetBodyID(vJoltBodyID);
		}
		else if (GetCapsuleCollider(_entityID))
		{
			CapsuleCollider* vCapsule = GetCapsuleCollider(_entityID);
			JPH::CapsuleShapeSettings s_capsuleSettings(vCapsule->GetHeight(), vCapsule->GetRadius());
			JPH::ShapeSettings::ShapeResult result = s_capsuleSettings.Create();
			JPH::ShapeRefC capsuleShape = result.Get();
			JPH::BodyCreationSettings b_capsuleSetting
			(
				capsuleShape,
				JoltToTDS::ToVec3(_transform->GetPosition()),
				JoltToTDS::ToQuat((_transform->GetRotation())),
				vMotionType,
				JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt())
			);
			b_capsuleSetting.mFriction = _rigidbody->GetFriction();
			b_capsuleSetting.mRestitution = _rigidbody->GetRestitution();
			b_capsuleSetting.mLinearVelocity = JoltToTDS::ToVec3(_rigidbody->GetLinearVel());
			b_capsuleSetting.mAngularVelocity = JoltToTDS::ToVec3(_rigidbody->GetAngularVel());

			JPH::BodyID capsuleID = m_pSystem->GetBodyInterface().CreateAndAddBody(b_capsuleSetting, JPH::EActivation::Activate);
			JoltBodyID vJoltBodyID(capsuleID.GetIndexAndSequenceNumber());
			TDS_INFO("Capsule Created!");
			_rigidbody->SetBodyID(vJoltBodyID);

		}
		else
		{
			TDS_ASSERT(false, "No collider found for entity, for now rigidbody need to have collider")
		}
		
	}
	/*
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
	*/
}
