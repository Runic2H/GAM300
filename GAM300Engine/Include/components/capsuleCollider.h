/*!*************************************************************************
****
\file capsuleCollider.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 21-10-2023
\brief  This program declares the functions in the Capsule Collider 
		component class
****************************************************************************
***/

#ifndef CAPSULECOLLIDERCOMPONENT
#define CAPSULECOLLIDERCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class CapsuleCollider : public IComponent
	{
	public:
		enum class Direction
		{
			X_AXIS,
			Y_AXIS,
			Z_AXIS
		};

		/*!*************************************************************************
		Initializes the Collider component when created
		****************************************************************************/
		DLL_API CapsuleCollider();
		/*!*************************************************************************
		Initializes the Collider component when created, given another Collider
		component to move (for ECS)
		****************************************************************************/
		DLL_API CapsuleCollider(CapsuleCollider&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Collider component class
		****************************************************************************/
		DLL_API ~CapsuleCollider() = default;
		/*!*************************************************************************
		Deserializes the Collider component
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the Collider component
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the Collider component class
		****************************************************************************/
		DLL_API bool& GetIsTrigger() { return mIsTrigger; }
		DLL_API void SetIsTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

		DLL_API Vec3& GetCenter() { return mCenter; }
		DLL_API void SetCenter(Vec3 center) { mCenter = center; }
		DLL_API void SetCenter(float x, float y, float z) { mCenter = Vec3(x, y, z); }

		DLL_API float& GetRadius() { return mRadius; }
		DLL_API void SetRadius(float radius) { mRadius = radius; }
		
		DLL_API float& GetHeight() { return mHeight; }
		DLL_API void SetHeight(float height) { mHeight = height; }
		
		DLL_API Direction& GetDirection() { return mDirection; }
		DLL_API void SetDirection(Direction direction) { mDirection = direction; }

	private:
		bool mIsTrigger;
		//Material mMaterial;
		Vec3 mCenter;
		float mRadius;
		float mHeight;
		Direction mDirection;
	};

	DLL_API CapsuleCollider* GetCapsuleCollider(EntityID entityID);
}

#endif
