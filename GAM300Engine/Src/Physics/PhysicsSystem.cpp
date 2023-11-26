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
#include "AssetManagement/AssetManager.h"


namespace TDS
{
	/*!*************************************************************************
	 * Static variables
	 ***************************************************************************/
	const double								PhysicsSystem::fixedDt = 0.0166666f;
	double										PhysicsSystem::accumulatedTime = 0.0f;
	std::unique_ptr<JPH::PhysicsSystem>			PhysicsSystem::m_pSystem;
	std::unique_ptr<JPH::TempAllocatorImpl>		PhysicsSystem::m_pTempAllocator;
	std::unique_ptr<JPH::JobSystemThreadPool>	PhysicsSystem::m_pJobSystem;
	std::unique_ptr<JPH::BodyManager>			PhysicsSystem::m_BodyManager;
	std::vector<JoltBodyID>					    PhysicsSystem::m_pBodyIDVector;
	
	BPLayerInterfaceImpl						broad_phase_layer_interface;
	ObjectVsBroadPhaseLayerFilterImpl			object_vs_broadphase_layer_filter;
	ObjectLayerPairFilterImpl					object_vs_object_layer_filter;
	MyBodyActivationListener body_activation_listener;
	MyContactListener contact_listener;

	/*!*************************************************************************
	 * Configuration
	 ***************************************************************************/
	const unsigned int cMaxBodies = 1024;				// Maximum number of bodies in the physics system
	const unsigned int cNumBodyMutexes = 0;				// Autodetect
	const unsigned int cMaxBodyPairs = 1024;			// Max amount of body pair for broadphrase detection
	const unsigned int cMaxContactConstraints = 1024;	// Maximum number of contact constraints
	
	static void TraceImpl(const char* inFMT, ...)
	{
		// Format the message
		va_list list;
		va_start(list, inFMT);
		char buffer[1024];
		vsnprintf(buffer, sizeof(buffer), inFMT, list);
		va_end(list);

		// Print to the TTY
		TDS_TRACE(buffer);
	}

#ifdef JPH_ENABLE_ASSERTS
	// Callback for asserts, connect this to your own assert handler if you have one
	static bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, JPH::uint inLine)
	{
		// Print to the TTY
		std::cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << std::endl;
		// Breakpoint
		return true;
	};
#endif

	void PhysicsSystem::PhysicsSystemInit()
	{
		// Initialize the Jolt Core
		using namespace JPH;
		// Register allocation hook
		RegisterDefaultAllocator();

		// Install callbacks
		Trace = TraceImpl;
		JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

		// Create a factory
		Factory::sInstance = new Factory();

		// Register all Jolt physics types
		RegisterTypes();

		m_pJobSystem = std::make_unique<JobSystemThreadPool>(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);
		// We need a temp allocator for temporary allocations during the physics update. We're
		// pre-allocating 10 MB to avoid having to do allocations during the physics update.
		// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
		// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
		// malloc / free.
		m_pTempAllocator = std::make_unique<TempAllocatorImpl>(10 * 1024 * 1024);

		//m_pSystem = std::make_unique<JPH::PhysicsSystem>();
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
		m_pSystem->SetBodyActivationListener(&body_activation_listener);

		// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		m_pSystem->SetContactListener(&contact_listener);
		std::cout << "successfully init Jolt Physics" << '\n';
	}

	void PhysicsSystem::PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, GraphicsComponent* _graphics)
	{
		static bool JPH_isPlay = false; // need to call only once in the update loop but it is a static function
		// Physics loop
		JPH::BodyInterface* pBodies = &m_pSystem->GetBodyInterface();
		if (!GetIsPlaying())
		{
			TypeReference<AssetModel>* AssetModel = nullptr;
			if (m_pSystem->GetNumBodies() != 0)
			{
				pBodies->RemoveBodies(JoltToTDS::ToBodyID(m_pBodyIDVector.data()), m_pBodyIDVector.size());
				pBodies->DestroyBodies(JoltToTDS::ToBodyID(m_pBodyIDVector.data()), m_pBodyIDVector.size());
				m_pBodyIDVector.clear();
			}
			for (int i = 0; i < entities.size(); ++i)
			{
				if (_rigidbody[i].GetBodyID().IsInvalid())
				{
					
					TDS_INFO("Init");
					
					TDS::AssetModel* tmp_assetModel = AssetManager::GetInstance()->GetModelFactory().GetModel(_graphics[i].GetModelName(), _graphics[i].GetAsset());
					std::string key = _graphics[i].GetMeshName();
					auto it = tmp_assetModel->m_Meshes.find(key);
					if (it != tmp_assetModel->m_Meshes.end())
					{
						MeshData* tmp_MeshData = &(it->second);
						Vec3 minBoundingBox(FLT_MAX, FLT_MAX, FLT_MAX);
						Vec3 maxBoundingBox(-FLT_MAX, -FLT_MAX, -FLT_MAX);
						for (auto &modelCoord : tmp_MeshData->m_VertexData)
						{
							minBoundingBox.x = Mathf::Min(minBoundingBox.x, modelCoord.m_Pos.x);
							minBoundingBox.y = Mathf::Min(minBoundingBox.y, modelCoord.m_Pos.y);
							minBoundingBox.z = Mathf::Min(minBoundingBox.z, modelCoord.m_Pos.z);

							maxBoundingBox.x = Mathf::Max(maxBoundingBox.x, modelCoord.m_Pos.x);
							maxBoundingBox.y = Mathf::Max(maxBoundingBox.y, modelCoord.m_Pos.y);
							maxBoundingBox.z = Mathf::Max(maxBoundingBox.z, modelCoord.m_Pos.z);

						}
						_rigidbody[i].setAABBmin(minBoundingBox);
						_rigidbody[i].setAABBmax(maxBoundingBox);
					}
					_graphics[i].setDebug(false);

					JPH_CreateBodyID(entities[i], &_transform[i], &_rigidbody[i]);
					
				}
			}
			
			m_pSystem->OptimizeBroadPhase();
			SetIsPlaying(true);
		}
		//TDS_INFO(m_pSystem->GetNumBodies());
		accumulatedTime += dt;		
		while (accumulatedTime >= TimeStep::GetFixedDeltaTime())
		{
			for (int i = 0; i < entities.size(); ++i)
			{
				if (!ecs.getEntityIsEnabled(entities[i]) || !ecs.getComponentIsEnabled<RigidBody>(entities[i]))
				{
					continue;
				}

				if (_rigidbody[i].GetBodyID().IsInvalid())
				{

					TDS_INFO("In Update Loop");
					JPH_CreateBodyID(entities[i], &_transform[i], &_rigidbody[i]);

				}
				using namespace JoltToTDS;
				EActivation mode = EActivation::Activate;
				pBodies->SetPosition(ToBodyID(_rigidbody[i]), ToVec3(_transform[i].GetPosition()), mode);
				pBodies->SetRotation(ToBodyID(_rigidbody[i]), ToQuat(_transform[i].GetRotation()), mode);
				
			}
			// JPH physics simulation
			//m_pSystem->Update(TimeStep::GetFixedDeltaTime(), 1, m_pTempAllocator.get(), m_pJobSystem.get());
			// Update back to the ECS
		
			for (int j = 0; j < entities.size(); ++j)
			{
				if (!ecs.getEntityIsEnabled(entities[j]) || !ecs.getComponentIsEnabled<RigidBody>(entities[j]))
				{
					continue;
				}
				if (contact_listener.GetSensorActivate())
				{
					int index = contact_listener.getSensorBodyID();
					if (_rigidbody[j].GetBodyID().GetIndexAndSequenceNumber() == index)
					{
						_rigidbody[j].setSensorActivate(true);
					}
				}
				else
				{
					_rigidbody[j].setSensorActivate(false);
				}

				Vec3 pos = _transform[j].GetPosition();
				Vec3 scale = _transform[j].GetScale();
				Vec3 rot = _transform[j].GetRotation();
				JPH_SystemUpdate(&_transform[j], &_rigidbody[j]);
				EventHandler::postChildTransformationEvent(entities[j], pos, scale, rot);

			}
			accumulatedTime -= TimeStep::GetFixedDeltaTime();
		}	
		
	}

	void PhysicsSystem::JPH_SystemUpdate(Transform* _transform, RigidBody* _rigidbody)
	{
		JPH::BodyID JPHBodyID = JoltToTDS::ToBodyID(*_rigidbody);
		JPH::BodyInterface* pBodies = &m_pSystem->GetBodyInterface();
		//_transform->SetPosition(JoltToTDS::ToVec3(pBodies->GetPosition(JPHBodyID)));
		//_transform->SetRotation(JoltToTDS::ToVec3(pBodies->GetRotation(JPHBodyID).GetEulerAngles()));
		//_rigidbody->SetLinearVel(JoltToTDS::ToVec3(pBodies->GetLinearVelocity(JPHBodyID)));
		//_rigidbody->SetAngularVel(JoltToTDS::ToVec3(pBodies->GetAngularVelocity(JPHBodyID)));
		//_transform->SetDirty(false);
	}
	void PhysicsSystem::SensorActivated(RigidBody* _rigidbody)
	{
		if (contact_listener.GetSensorActivate())
		{
			_rigidbody->setSensorActivate(true);

		}
		else
		{
			_rigidbody->setSensorActivate(false);
		}
	}
	void PhysicsSystem::JPH_SystemShutdown()
	{
		m_pTempAllocator = nullptr;
		m_pSystem = nullptr;
		m_pJobSystem = nullptr;
		m_BodyManager = nullptr;
	
	}
	void PhysicsSystem::JPH_CreateBodyID(const EntityID& _entityID, Transform* _transform, RigidBody* _rigidbody)
	{
		EMotionType vMotionType = JoltToTDS::ToEMotionType(_rigidbody->GetMotionType());
		if (GetSphereCollider(_entityID))
		{
			SphereCollider* vSphere = GetSphereCollider(_entityID);
			JPH::SphereShapeSettings s_sphereSettings(_transform->GetScale().x / (vSphere->GetRadius() * 2.f));
			JPH::ShapeSettings::ShapeResult result = s_sphereSettings.Create();
			JPH::ShapeRefC sphereShape = result.Get(); // if error, high chance is how the shape is created, radius cannot be 0!
			JPH::BodyCreationSettings b_sphereSetting
			(
				sphereShape,
				JoltToTDS::ToVec3(_transform->GetPosition()),
				JoltToTDS::ToQuat((_transform->GetRotation())),
				vMotionType,
				JoltLayers::GetObjectLayer(_rigidbody->GetMotionTypeInt())
			);
			b_sphereSetting.mFriction = _rigidbody->GetFriction();
			b_sphereSetting.mRestitution = _rigidbody->GetRestitution();
			b_sphereSetting.mGravityFactor = (_rigidbody->GetUseGravity()) ? _rigidbody->GetGravityFactor() : 0.0f;
			b_sphereSetting.mLinearDamping = _rigidbody->GetLinearDamping();
			b_sphereSetting.mAngularDamping = _rigidbody->GetAngularDamping();
			b_sphereSetting.mLinearVelocity = JoltToTDS::ToVec3(_rigidbody->GetLinearVel());
			b_sphereSetting.mAngularVelocity = JoltToTDS::ToVec3(_rigidbody->GetAngularVel());
			b_sphereSetting.mIsSensor = vSphere->GetIsTrigger();

			JPH::BodyID sphereID = m_pSystem->GetBodyInterface().CreateAndAddBody(b_sphereSetting, JPH::EActivation::Activate);
			JoltBodyID vJoltBodyID(sphereID.GetIndexAndSequenceNumber());
			m_pBodyIDVector.push_back(vJoltBodyID);
			TDS_INFO("Sphere Created!");
			_rigidbody->SetBodyID(vJoltBodyID);
		}
		else if (GetBoxCollider(_entityID))
		{
			BoxCollider* vBox = GetBoxCollider(_entityID);
			//float transX, transY, transZ;
			Vec3 length = (_rigidbody->getAABBmax() - _rigidbody->getAABBmin());
			if (length.x == 0.f)
			{
				length.x = _rigidbody->getAABBmax().x;
			}
			if (length.y == 0.f)
			{
				length.y = _rigidbody->getAABBmax().y;
			}
			if (length.z == 0.f)
			{
				length.z = _rigidbody->getAABBmax().z;
			}
			//Vec3 halfExtents = { _transform->GetScale().x / vBox->GetSize().x, _transform->GetScale().y / vBox->GetSize().y, _transform->GetScale().z / vBox->GetSize().z };
			//halfExtents = (halfExtents) * 2.f;
			JPH::Vec3 JPHextents = JoltToTDS::ToVec3(length);
			JPH::BoxShapeSettings s_boxSettings(JPHextents);
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
			b_BoxSetting.mGravityFactor = _rigidbody->GetGravityFactor();
			b_BoxSetting.mLinearDamping = _rigidbody->GetLinearDamping();
			b_BoxSetting.mAngularDamping = _rigidbody->GetAngularDamping();
			b_BoxSetting.mLinearVelocity = JoltToTDS::ToVec3(_rigidbody->GetLinearVel());
			b_BoxSetting.mAngularVelocity = JoltToTDS::ToVec3(_rigidbody->GetAngularVel());
			b_BoxSetting.mIsSensor = vBox->GetIsTrigger();


			JPH::BodyID boxID = m_pSystem->GetBodyInterface().CreateAndAddBody(b_BoxSetting, JPH::EActivation::Activate);
			JoltBodyID vJoltBodyID(boxID.GetIndexAndSequenceNumber());
			m_pBodyIDVector.push_back(vJoltBodyID);
			TDS_INFO("Box Created!");
			_rigidbody->SetBodyID(vJoltBodyID);
		}
		else if (GetCapsuleCollider(_entityID))
		{
			CapsuleCollider* vCapsule = GetCapsuleCollider(_entityID);
			JPH::CapsuleShapeSettings s_capsuleSettings(vCapsule->GetHeight()*2.f, vCapsule->GetRadius()*2.f);
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
			b_capsuleSetting.mGravityFactor = _rigidbody->GetGravityFactor();
			b_capsuleSetting.mLinearDamping = _rigidbody->GetLinearDamping();
			b_capsuleSetting.mAngularDamping = _rigidbody->GetAngularDamping();
			b_capsuleSetting.mLinearVelocity = JoltToTDS::ToVec3(_rigidbody->GetLinearVel());
			b_capsuleSetting.mAngularVelocity = JoltToTDS::ToVec3(_rigidbody->GetAngularVel());
			b_capsuleSetting.mIsSensor = vCapsule->GetIsTrigger();
			
			JPH::BodyID capsuleID = m_pSystem->GetBodyInterface().CreateAndAddBody(b_capsuleSetting, JPH::EActivation::Activate);
			
			JoltBodyID vJoltBodyID(capsuleID.GetIndexAndSequenceNumber());
			m_pBodyIDVector.push_back(vJoltBodyID);

			TDS_INFO("Capsule Created!");
			_rigidbody->SetBodyID(vJoltBodyID);

		}
		else
		{
			TDS_ASSERT(false, "No collider found for entity, for now rigidbody need to have collider")
		}
		
	}
}
