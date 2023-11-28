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

#ifndef SPHERECOLLIDERCOMPONENT
#define SPHERECOLLIDERCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class SphereCollider : public IComponent
	{
	public:
		enum class Direction
		{
			X_AXIS,
			Y_AXIS,
			Z_AXIS
		};
		enum class AImode
		{
			NONE = 0,
			MONSTER,
			PLAYER,
			INTERACTABLE
		};

		/*!*************************************************************************
		Initializes the Collider component when created
		****************************************************************************/
		DLL_API SphereCollider();
		/*!*************************************************************************
		Initializes the Collider component when created, given another Collider
		component to move (for ECS)
		****************************************************************************/
		DLL_API SphereCollider(SphereCollider&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Collider component class
		****************************************************************************/
		DLL_API ~SphereCollider() = default;
		/*!*************************************************************************
		Getter and setter functions for the variables in the Collider component class
		****************************************************************************/
		DLL_API bool& GetIsTrigger() { return mIsTrigger; }
		DLL_API void SetIsTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

		DLL_API bool& GetIsInteract() { return mIsInteract; }
		DLL_API void SetIsInteract(bool input) { mIsInteract = input; }

		DLL_API Vec3& GetCenter() { return mCenter; }
		DLL_API void SetCenter(Vec3 center) { mCenter = center; }
		DLL_API void SetCenter(float x, float y, float z) { mCenter = Vec3(x, y, z); }

		DLL_API float& GetRadius() { return mRadius; }
		DLL_API void SetRadius(float radius) { mRadius = radius; }

		DLL_API void SetAImode(AImode mode) { AI = mode; }
		DLL_API AImode& getAImode() { return AI; }

		DLL_API void setColliderName(std::string name) { mColliderName = name; }
		DLL_API std::string& getColliderName() { return mColliderName; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		bool mIsTrigger;
		bool mIsInteract;
		//Material mMaterial;
		Vec3 mCenter;
		float mRadius;
		AImode AI;
		std::string mColliderName;
	};

	DLL_API SphereCollider* GetSphereCollider(EntityID entityID);
}

#endif
