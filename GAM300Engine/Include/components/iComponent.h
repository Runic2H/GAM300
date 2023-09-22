#ifndef ICOMPONENTS
#define ICOMPONENTS

#include <imgui/imgui.h>
#include "imguiHelper/ImguiFunctionHelper.h"
#include <string>

#include "sceneManager/serialization.h"


namespace TDS
{
	class IComponent : public Serializer
	{
	public:
		virtual ~IComponent() = default;
		virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;

		virtual void ImGuiDisplay() = 0;
	};
}

#endif