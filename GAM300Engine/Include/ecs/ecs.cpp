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
#include "camera/Camerasystem/CameraSystem.h"
#include "eventManager/eventHandler.h"
#include "Physics/CollisionSystem.h"

namespace TDS
{
	/*!*************************************************************************
	This function binds functions of the systems to the ECS to run
	****************************************************************************/
	void bindSystemFunctions()
	{
		_PhysicsSystem.action(PhysicsSystem::PhysicsSystemInit, PhysicsSystem::PhysicsSystemUpdate);
		_AISystem.action(AISystem::AISystemInit, AISystem::AISystemUpdate);
		_CameraSystem.action(CameraSystem::CameraSystemInit, CameraSystem::CameraSystemUpdate);
		_EventHandler_ChildTransform.action(EventHandler::childTransformationHandlerInit, EventHandler::childTransformationHandlerUpdate);
		_ColliderDebugSystem.action(CollisionSystem::CollisionSystemInit, CollisionSystem::CollisionSystemUpdate);
		_RenderSystem.action(RendererSystem::OnInit, RendererSystem::OnUpdate);
	}
}
