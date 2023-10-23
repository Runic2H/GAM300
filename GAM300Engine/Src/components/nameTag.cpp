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
		.method("GetNameTag", &NameTag::GetNameTag)
		.method("SetNameTag", &NameTag::SetNameTag)
		.property("Name", &NameTag::mName)
		.method("GetHierarchyParent", &NameTag::GetHierarchyParent)
		.method("SetHierarchyParent", &NameTag::SetHierarchyParent)
		.property("HierarchyParent", &NameTag::mHierarchyParent)
		.method("GetHierarchyIndex", &NameTag::GetHierarchyIndex)
		.method("SetHierarchyIndex", &NameTag::SetHierarchyIndex)
		.property("HierarchyIndex", &NameTag::mHierarchyIndex);
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the NameTag component when created
	****************************************************************************/
	NameTag::NameTag() : mName				("New Entity"),
						 mHierarchyParent	(0),
						 mHierarchyIndex	(0)
	{ }

	/*!*************************************************************************
	Initializes the NameTag component when created, given another NameTag
	component to move (for ECS)
	****************************************************************************/
	NameTag::NameTag(NameTag&& toMove) noexcept : mName				(toMove.mName),
												  mHierarchyParent	(toMove.mHierarchyParent),
												  mHierarchyIndex	(toMove.mHierarchyIndex)
	{ }
}
