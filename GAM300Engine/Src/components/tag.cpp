/*!*************************************************************************
****
\file tag.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Tag component class
****************************************************************************
***/

#include "components/tag.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<Tag>("Tag")
		.property("Tag", &Tag::GetTag, &Tag::SetTag)
		.property("mTargetTag", &Tag::GetTargetTag, &Tag::SetTargetTag);

}

namespace TDS
{
	/*!*************************************************************************
	Initializes the Tag component when created
	****************************************************************************/
	Tag::Tag() : mTag		("none"),
				 mTargetTag	("none")
	{ }

	/*!*************************************************************************
	Initializes the Tag component when created, given another Tag component to 
	move (for ECS)
	****************************************************************************/
	Tag::Tag(Tag&& toMove) noexcept : mTag			(toMove.mTag),
									  mTargetTag	(toMove.mTargetTag)
	{ }
}
