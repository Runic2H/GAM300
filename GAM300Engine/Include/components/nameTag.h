/*!*************************************************************************
****
\file nameTag.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the nameTag component class
****************************************************************************
***/

#ifndef NAMETAGCOMPONENT
#define NAMETAGCOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class NameTag : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the NameTag component when created
		****************************************************************************/
		DLL_API NameTag();
		/*!*************************************************************************
		Initializes the NameTag component when created, given another NameTag
		component to move (for ECS)
		****************************************************************************/
		DLL_API NameTag(NameTag&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the NameTag component class
		****************************************************************************/
		DLL_API ~NameTag() = default;
		/*!*************************************************************************
		Getter and setter functions for the variables in the NameTag component class
		****************************************************************************/
		DLL_API std::string GetName() { return mName; }
		DLL_API void SetName(std::string name) { mName = name; }

		DLL_API std::string GetTag() { return mTag; }
		DLL_API void SetTag(std::string tag) { mTag = tag; }

		DLL_API bool GetIsActive() { return mIsActive; }
		DLL_API void SetIsActive(bool isActive) { mIsActive = isActive; }

		DLL_API EntityID GetHierarchyParent() { return mHierarchyParent; }
		DLL_API void SetHierarchyParent(EntityID hierarchyParent) { mHierarchyParent = hierarchyParent; }
		
		DLL_API int GetHierarchyIndex() { return mHierarchyIndex; }
		DLL_API void SetHierarchyIndex(int hierarchyIndex) { mHierarchyIndex = hierarchyIndex; }
		
		DLL_API std::vector<EntityID>& GetHierarchyChildren() { return mHierarchyChildren; }

		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		std::string mName;
		std::string mTag;
		bool mIsActive;

		EntityID mHierarchyParent;
		int mHierarchyIndex;
		std::vector<EntityID> mHierarchyChildren;
	};

	DLL_API NameTag* GetNameTag(EntityID entityID);
}

#endif // NAMETAGCOMPONENT