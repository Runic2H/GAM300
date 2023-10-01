/*!*************************************************************************
****
\file playerAttributes.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the PlayerAttributes 
		component class
****************************************************************************
***/

#include "components/playerAttributes.h"

namespace TDS
{
	/*!*************************************************************************
	Deserializes the PlayerAttributes component
	****************************************************************************/
	bool PlayerAttributes::Deserialize(const rapidjson::Value& obj)
	{
		//UNREFERENCED_PARAMETER(obj);
		obj;
		return true;
	}

	/*!*************************************************************************
	Serializes the PlayerAttributes component
	****************************************************************************/
	bool PlayerAttributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//UNREFERENCED_PARAMETER(writer);
		writer;
		return true;
	}
}