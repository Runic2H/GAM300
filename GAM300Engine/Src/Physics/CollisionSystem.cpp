/*!*****************************************************************************
 * \file          CollisionSystem.cpp
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Implementation of the collision system.
 *******************************************************************************/
#include "Physics/CollisionSystem.h"

namespace TDS
{
	void CollisionSystem::CollisionSystemInit()
	{
	}
	
	void CollisionSystem::CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, GraphicsComponent* _graphics)
	{
		for (int i = 0; i < entities.size(); ++i)
		{
			if (GetSphereCollider(entities[i]))
			{
				SphereCollider* vSphere = GetSphereCollider(entities[i]);
				_transform[i].SetOffSetPos(vSphere->GetCenter());
				float radius = vSphere->GetRadius() * 2.f;
				Vec3 vScale = Vec3(radius) - Vec3(1.f);
				_transform[i].SetOffSetScale(vScale);
			}
			
			else if (GetBoxCollider(entities[i]))
			{
				BoxCollider* vBox = GetBoxCollider(entities[i]);
				_transform[i].SetOffSetPos(vBox->GetCenter());
				Vec3 vScale = vBox->GetSize() - Vec3(1.f);
				_transform[i].SetOffSetScale(vScale);
			}

			else if (GetCapsuleCollider(entities[i]))
			{
				CapsuleCollider* vCapsule = GetCapsuleCollider(entities[i]);
				_transform[i].SetOffSetPos(vCapsule->GetCenter());
				float vRadius = vCapsule->GetRadius() * 2.f;
				float vHeight = vCapsule->GetHeight() / 2.f;
				Vec3 vScale = Vec3(vRadius, vHeight, vRadius) - Vec3(1.f);
				_transform[i].SetOffSetScale(vScale);
			}
		}
	}

	
}

