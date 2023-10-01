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

namespace TDS
{
	/*!*************************************************************************
	Initializes the NameTag component when created
	****************************************************************************/
	NameTag::NameTag() : mName("New Entity") 
	{ }

	/*!*************************************************************************
	Initializes the NameTag component when created, given another NameTag
	component to move (for ECS)
	****************************************************************************/
	NameTag::NameTag(NameTag&& toMove) noexcept : mName(toMove.mName)
	{ }

	/*!*************************************************************************
	Deserializes the NameTag component
	****************************************************************************/
	bool NameTag::Deserialize(const rapidjson::Value& obj)
	{
		mName = obj["name"].GetString();
		return true;
	}

	/*!*************************************************************************
	Serializes the NameTag component
	****************************************************************************/
	bool NameTag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("name");
		writer->String(mName.c_str());
		return true;
	}
}
