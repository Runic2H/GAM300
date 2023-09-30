#include "ecs/systems.h"

#include "physics/physicsSystem.h"
#include "AI/aiSystem.h"

namespace TDS
{
	void bindSystemFunctions()
	{
		_PhysicsSystem.action(PhysicsSystem::PhysicsSystemInit, PhysicsSystem::PhysicsSystemUpdate);
		_AISystem.action(AISystem::AISystemInit, AISystem::AISystemUpdate);
	}
}
