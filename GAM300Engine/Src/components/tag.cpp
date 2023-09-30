#include "components/tag.h"

namespace TDS
{
	Tag::Tag() : mTag		("none"),
				 mTargetTag	("none")
	{ }

	Tag::Tag(Tag&& toMove) noexcept : mTag			(toMove.mTag),
									  mTargetTag	(toMove.mTargetTag)
	{ }

	bool Tag::Deserialize(const rapidjson::Value& obj)
	{
		mTag = obj["tag"].GetString();
		mTargetTag = obj["targetTag"].GetString();

		return true;
	}

	bool Tag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("tag");
		writer->String(mTag.c_str());
		
		writer->Key("target");
		writer->String(mTargetTag.c_str());

		return true;
	}

	//void Tag::ImGuiDisplay()
	//{
	//	ImguiTextInput("Tag", mTag);
	//	ImguiTextInput("Target Tag", mTargetTag);
	//}
}
