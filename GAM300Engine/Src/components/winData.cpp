#include "components/winData.h"

namespace TDS
{
	WinData::WinData() : mTitle				("Disinheritance"),
						 mWidth				(1920),
						 mHeight			(1080),
						 mCurrentWidth		(1920),
						 mCurrentHeight		(1080),
						 mMasterVolume		(1.0f),
						 mBGMVolume			(1.0f),
						 mSFXVolume			(1.0f)
	{ }

	bool WinData::Deserialize(const rapidjson::Value& obj)
	{
		mTitle = obj["title"].GetString();
		mWidth = obj["width"].GetUint();
		mHeight = obj["height"].GetUint();
		mCurrentWidth = obj["currentWidth"].GetUint();
		mCurrentHeight = obj["currentHeight"].GetFloat();
		mMasterVolume = obj["masterVolume"].GetFloat();
		mBGMVolume = obj["BGMVolume"].GetFloat();
		mSFXVolume = obj["SFXVolume"].GetFloat();

		return true;
	}

	bool WinData::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("title");
		writer->String(mTitle.c_str());

		writer->Key("width");
		writer->Uint(mWidth);
		writer->Key("height");
		writer->Uint(mHeight);

		writer->Key("currentWidth");
		writer->Uint(mCurrentWidth);
		writer->Key("currentHeight");
		writer->Uint(mCurrentHeight);

		writer->Key("masterVolume");
		writer->Double(mMasterVolume);
		writer->Key("BGMVolume");
		writer->Double(mBGMVolume);
		writer->Key("SFXVolume");
		writer->Double(mSFXVolume);

		return true;
	}

	void WinData::ImGuiDisplay()
	{

	}
}
