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

	/*!*************************************************************************
	Deserializes the Tag component
	****************************************************************************/
	bool Tag::Deserialize(const rapidjson::Value& obj)
	{
		mTag = obj["tag"].GetString();
		mTargetTag = obj["targetTag"].GetString();

		return true;
	}

	/*!*************************************************************************
	Serializes the Tag component
	****************************************************************************/
	bool Tag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("tag");
		writer->String(mTag.c_str());
		
		writer->Key("target");
		writer->String(mTargetTag.c_str());

		return true;
	}
}
