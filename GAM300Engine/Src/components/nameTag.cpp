/*!*************************************************************************
****
\file nameTag.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the NameTag component class
****************************************************************************
***/

#include "components/nameTag.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<NameTag>("Name Tag")
		.property("Name", &NameTag::GetName, &NameTag::SetName)
		.property("Tag", &NameTag::GetTag, &NameTag::SetTag)
		.property("IsActive", &NameTag::GetIsActive, &NameTag::SetIsActive)
		.property("HierarchyParent", &NameTag::GetHierarchyParent, &NameTag::SetHierarchyParent)
		.property("HierarchyIndex", &NameTag::GetHierarchyIndex, &NameTag::SetHierarchyIndex);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the NameTag component when created
	****************************************************************************/
	NameTag::NameTag() : mName				("New Entity"),
						 mTag				(""),
						 mIsActive			(true),
						 mHierarchyParent	(0),
						 mHierarchyIndex	(0)
	{ }

	/*!*************************************************************************
	Initializes the NameTag component when created, given another NameTag
	component to move (for ECS)
	****************************************************************************/
	NameTag::NameTag(NameTag&& toMove) noexcept : mName				(toMove.mName),
												  mTag				(toMove.mTag),
												  mIsActive			(toMove.mIsActive),
												  mHierarchyParent	(toMove.mHierarchyParent),
												  mHierarchyIndex	(toMove.mHierarchyIndex)
	{ }

	NameTag* GetNameTag(EntityID entityID)
	{
		return ecs.getComponent<NameTag>(entityID);
	}
}
