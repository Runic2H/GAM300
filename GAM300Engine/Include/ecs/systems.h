/*!*************************************************************************
****
\file systems.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares and registers the systems in the ECS
****************************************************************************
***/

#ifndef SYSTEMS
#define SYSTEMS

#include "ecs/ecs.h"
#include "components/components.h"

// DONT INCLUDE THIS ANYWHERE BUT ECS.CPP

namespace TDS
{
	DLL_API ECS ecs;

	// Layer 1 - Run only on play
	// Layer 2 - Always running

	ECSSystem<Transform, RigidBody>					_PhysicsSystem(1);
	ECSSystem<Transform, RigidBody, SphereCollider>	_ColliderSystem(1);
	ECSSystem<AI>									_AISystem(1);
	ECSSystem<Transform, GraphicsComponent>			_RenderSystem(2);
	ECSSystem<RigidBody>							_JoltSystem(2);
}

#endif // SYSTEMS