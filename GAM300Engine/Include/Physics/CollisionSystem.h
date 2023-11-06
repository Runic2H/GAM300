/*!*****************************************************************************
 * \file          CollisionSystem.h
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         The system that check and handle collision.
 *******************************************************************************/
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ecs/ecs.h"
#include "components/sphereCollider.h"
#include "components/boxCollider.h"
#include "components/capsuleCollider.h"
#include "components/transform.h"
#include "components/GraphicsComponent.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API CollisionSystem
	{
	public:
		/*!*************************************************************************
		 * Collision System Init and Update (Will be used by the ECS)
		 ***************************************************************************/
		static void CollisionSystemInit();
		// Main purpose is to get the offset value from each collider and pass to graphics for render
		static void CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, GraphicsComponent* _graphics);
		
	private:
	};
}


#endif // !COLLISIONSYSTEM_H
