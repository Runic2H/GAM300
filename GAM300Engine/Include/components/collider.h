/*!*************************************************************************
****
\file collider.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the Collider component class
****************************************************************************
***/

#ifndef COLLIDERCOMPONENT
#define COLLIDERCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class Collider : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the Collider component when created
		****************************************************************************/
		DLL_API Collider();
		/*!*************************************************************************
		Initializes the Collider component when created, given another Collider
		component to move (for ECS)
		****************************************************************************/
		DLL_API Collider(Collider&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Collider component class
		****************************************************************************/
		DLL_API ~Collider() = default;
		/*!*************************************************************************
		Getter and setter functions for the variables in the Collider component class
		****************************************************************************/
		DLL_API Vec3& GetColliderNormal() { return mCollisionNormal; }
		DLL_API void SetColliderNormal(Vec3 collisionNormal) { mCollisionNormal = collisionNormal; }
		DLL_API void SetColliderNormal(float x, float y, float z) { mCollisionNormal = Vec3(x, y, z); }

		DLL_API Vec3& GetMin() { return mMin; }
		DLL_API void SetMin(Vec3 min) { mMin = min; }
		DLL_API void SetMin(float x, float y, float z) { mMin = Vec3(x, y, z); }

		DLL_API Vec3& GetMax() { return mMax; }
		DLL_API void SetMax(Vec3 max) { mMax = max; }
		DLL_API void SetMax(float x, float y, float z) { mMax = Vec3(x, y, z); }

		DLL_API Vec3& GetOffset() { return mOffset; }
		DLL_API void SetOffset(Vec3 offset) { mOffset = offset; }
		DLL_API void SetOffset(float x, float y, float z) { mOffset = Vec3(x, y, z); }

		DLL_API int& GetHit() { return mHit; }
		DLL_API void SetHit(int hit) { mHit = hit; }

		DLL_API float& GetRadius() { return mRadius; }
		DLL_API void SetRadius(float radius) { mRadius = radius; }

		DLL_API bool& GetAlive() { return mIsAlive; }
		DLL_API void SetAlive(bool isAlive) { mIsAlive = isAlive; }

		DLL_API bool& GetCollision() { return mCollision; }
		DLL_API void SetCollision(bool collision) { mCollision = collision; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		Vec3 mCollisionNormal;
		Vec3 mMin;
		Vec3 mMax;
		Vec3 mOffset;
		int mHit;
		
		float mRadius;
		
		bool mIsAlive;
		bool mCollision;
	};

	DLL_API Collider* GetCollider(EntityID entityID);
}

#endif // COLLIDERCOMPONENT