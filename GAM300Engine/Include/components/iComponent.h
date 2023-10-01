#ifndef ICOMPONENTS
#define ICOMPONENTS

//#include "../GAM300Editor/Include/imguiHelper/ImguiHelper.h"
#include <string>

#include "sceneManager/serialization.h"


namespace TDS
{
	class DLL_API IComponent : public Serializer
	{
	public:
		virtual ~IComponent() = default;
		virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;
	};
}

#endif