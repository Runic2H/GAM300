/*!*************************************************************************
****
\file ecs.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines functions for the bunding of the systems to 
		the ECS
****************************************************************************
***/

#include "ecs/systems.h"

#include "physics/physicsSystem.h"
#include "AI/aiSystem.h"
#include "Rendering/RendererSystem.h"

namespace TDS
{
	/*!*************************************************************************
	This function binds functions of the systems to the ECS to run
	****************************************************************************/
	void bindSystemFunctions()
	{
		_PhysicsSystem.action(PhysicsSystem::PhysicsSystemInit, PhysicsSystem::PhysicsSystemUpdate);
		_AISystem.action(AISystem::AISystemInit, AISystem::AISystemUpdate);
		_RenderSystem.action(RendererSystem::OnInit, RendererSystem::OnUpdate);
		//_AudioSystem.action(AudioWerks::AudioEngine::init, AudioWerks::AudioEngine::update);
	}
}
