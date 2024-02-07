/*!*************************************************************************
****
\file boxCollider.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 21-10-2023
\brief  This program declares the functions in the Box Collider component 
		class
****************************************************************************
***/

#ifndef BOXCOLLIDERCOMPONENT
#define BOXCOLLIDERCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class BoxCollider : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the Collider component when created
		****************************************************************************/
		DLL_API BoxCollider();
		/*!*************************************************************************
		Initializes the Collider component when created, given another Collider
		component to move (for ECS)
		****************************************************************************/
		DLL_API BoxCollider(BoxCollider&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Collider component class
		****************************************************************************/
		DLL_API ~BoxCollider() = default;
		/*!*************************************************************************
		Getter and setter functions for the variables in the Collider component class
		****************************************************************************/
		DLL_API bool& GetIsTrigger() { return mIsTrigger; }
		DLL_API void SetIsTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

		DLL_API Vec3& GetColliderCenter() { return mColliderCenter; }
		DLL_API void SetColliderCenter(Vec3 center) { mColliderCenter = center; }
		DLL_API void SetColliderCenter(float x, float y, float z) { mColliderCenter = Vec3(x, y, z); }

		DLL_API Vec3& GetColliderSize() { return mColliderSize; }
		DLL_API void SetColliderSize(Vec3 size) { mColliderSize = size; }
		DLL_API void SetColliderSize(float x, float y, float z) { mColliderSize = Vec3(x, y, z); }

		DLL_API Vec3& GetColliderScale() { return mColliderScale; }
		DLL_API void SetColliderScale(Vec3 scale) { mColliderScale = scale; }

		DLL_API Vec3& GetModelRotation() { return modelRotation; }
		DLL_API void SetModelRotation(Vec3 rotation) { modelRotation = rotation; }

		DLL_API Vec3& GetOffsetScale() { return mOffsetScale; }
		DLL_API void SetOffsetScale(Vec3 input) { mOffsetScale = input; }

		DLL_API Vec3& GetOffsetCenter() { return mOffsetCenter; }
		DLL_API void SetOffsetCenter(Vec3 input) { mOffsetCenter = input; }

		DLL_API bool& GetModelInit() { return modelInit; }
		DLL_API void SetModelInit(bool input) { modelInit = input; }

		DLL_API Vec3& GetModelScale() { return modelScale; }
		DLL_API void SetModelScale(Vec3 input) { modelScale = input; }

		DLL_API Vec3& GetModelCenter() { return modelCenter; }
		DLL_API void SetModelCenter(Vec3 input) { modelCenter = input; }

		DLL_API Vec3& GetModelSize() { return modelSize; }
		DLL_API void SetModelSize(Vec3 input) { modelSize = input; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		bool mIsTrigger;
		//Material mMaterial;
		Vec3 mColliderCenter;
		Vec3 mColliderSize;
		Vec3 mColliderScale;

		Vec3 mOffsetScale;
		Vec3 mOffsetCenter;

		bool modelInit;
		Vec3 modelScale; // scale factor (1,1,1) is default
		Vec3 modelCenter;
		Vec3 modelSize; // length width height
		Vec3 modelRotation;

	};

	DLL_API BoxCollider* GetBoxCollider(EntityID entityID);
}

#endif
