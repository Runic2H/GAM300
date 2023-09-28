#include "ecs.h"
#include "ecs/systems.h"

#include "physics/physicsSystem.h"
#include "AI/aiSystem.h"

namespace TDS
{
	std::uint32_t                 ECS::systemCount = 0;
	std::uint32_t                 ECS::componentCount = 0;
	ECS::EntityArchetypeMap       ECS::mEntityArchetypeMap;
	ECS::ArchetypesArray          ECS::mArchetypes;
	EntityID                      ECS::mEntityIdCounter = 1;
	ECS::ComponentTypeIDBaseMap   ECS::mComponentMap;

	void bindSystemFunctions()
	{
		_PhysicsSystem.action(PhysicsSystem::PhysicsSystemInit, PhysicsSystem::PhysicsSystemUpdate);
		_AISystem.action(AISystem::AISystemInit, AISystem::AISystemUpdate);
	}
}
