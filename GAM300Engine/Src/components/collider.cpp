/*!*************************************************************************
****
\file collider.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Collider component class
****************************************************************************
***/

#include "components/collider.h"

namespace TDS 
{
	/*!*************************************************************************
	Initializes the Collider component when created
	****************************************************************************/
	Collider::Collider() : mCollisionNormal (Vec3(0.0f, 0.0f, 0.0f)),
						   mMin				(Vec3(0.0f, 0.0f, 0.0f)),
						   mMax				(Vec3(0.0f, 0.0f, 0.0f)),
						   mOffset			(Vec3(0.0f, 0.0f, 0.0f)),
						   mHit				(0),
						   mRadius			(0.0f),
						   mIsAlive			(true),
						   mCollision		(false)
	{ }

	/*!*************************************************************************
	Initializes the Collider component when created, given another Collider
	component to move (for ECS)
	****************************************************************************/
	Collider::Collider(Collider&& toMove) noexcept : mCollisionNormal(toMove.mCollisionNormal),
													 mMin(toMove.mMin),
													 mMax(toMove.mMax),
													 mOffset(toMove.mOffset),
													 mHit(toMove.mHit),
													 mRadius(toMove.mRadius),
													 mIsAlive(toMove.mIsAlive)
	{ }

	Collider* GetCollider(EntityID entityID)
	{
		return ecs.getComponent<Collider>(entityID);
	}
}