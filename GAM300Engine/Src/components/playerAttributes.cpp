#include "components/playerAttributes.h"

namespace TDS
{
	/*!*************************************************************************
	Deserialize for PlayerAttributes
	****************************************************************************/
	bool PlayerAttributes::Deserialize(const rapidjson::Value& obj)
	{
		//UNREFERENCED_PARAMETER(obj);
		obj;
		return true;
	}

	/*!*************************************************************************
	Serialize for PlayerAttributes
	****************************************************************************/
	bool PlayerAttributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//UNREFERENCED_PARAMETER(writer);
		writer;
		return true;
	}

	//void PlayerAttributes::ImGuiDisplay()
	//{

	//}
}