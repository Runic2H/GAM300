#ifndef SYSTEMS
#define SYSTEMS

#include "ecs/ecs.h"
#include "components/components.h"

// DONT INCLUDE THIS ANYWHERE BUT ECS.CPP

namespace TDS
{
	DLL_API ECS ecs;

	//std::unique_ptr<ECS> ECS::m_instance;

	System<Transform, RigidBody>				_PhysicsSystem(1);
	System<Transform, RigidBody, Collider>		_ColliderSystem(1);
	System<AI>									_AISystem(1);
	//System<Transform, RigidBody> _AISystem(1);
	//System<Transform> _GraphicsSystem(1);
}

#endif // SYSTEMS