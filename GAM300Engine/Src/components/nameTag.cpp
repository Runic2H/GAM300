#include "components/nameTag.h"

namespace TDS
{
	NameTag::NameTag() : mName("New Entity") 
	{ }

	NameTag::NameTag(NameTag&& toMove) noexcept : mName(toMove.mName)
	{ }

	bool NameTag::Deserialize(const rapidjson::Value& obj)
	{
		mName = obj["name"].GetString();
		return true;
	}

	bool NameTag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("name");
		writer->String(mName.c_str());
		return true;
	}

	//void NameTag::ImGuiDisplay()
	//{
	//	//ImGui::NewLine();

	//	//ImGui::Indent();

	//	ImguiTextInput("Name", mName);

	//	//ImGui::Unindent();
	//}
}
