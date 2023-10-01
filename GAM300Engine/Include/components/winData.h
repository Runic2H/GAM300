#ifndef WINDATACOMPONENT
#define WINDATACOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API WinData : public IComponent
	{
	public:
		WinData();
		WinData(WinData&& toMove) noexcept;
		~WinData() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		std::string GetTitle() { return mTitle; }
		void SetTitle(std::string title) { mTitle = title; }

		std::uint32_t GetWidth() { return mWidth; }
		void SetWidth(std::uint32_t width) { mWidth = width; }

		std::uint32_t GetHeight() { return mHeight; }
		void SetHeight(std::uint32_t height) { mHeight = height; }

		std::uint32_t GetCurrentWidth() { return mCurrentWidth; }
		void SetCurrentWidth(std::uint32_t currentWidth) { mCurrentWidth = currentWidth; }

		std::uint32_t GetCurrentHeight() { return mCurrentHeight; }
		void SetCurrentHeight(std::uint32_t currentHeight) { mCurrentHeight = currentHeight; }
		
		float GetMasterVolume() { return mMasterVolume; }
		void SetMasterVolume(float masterVolume) { mMasterVolume = masterVolume; }
		
		float GetBGMVolume() { return mBGMVolume; }
		void SetBGMVolume(float BGMVolume) { mBGMVolume = BGMVolume; }
		
		float GetSFXVolume() { return mSFXVolume; }
		void SetSFXVolume(float SFXVolume) { mSFXVolume = SFXVolume; }

	private:
		std::string mTitle;
		std::uint32_t mWidth;
		std::uint32_t mHeight;
		std::uint32_t mCurrentWidth;
		std::uint32_t mCurrentHeight;
		float mMasterVolume;
		float mBGMVolume;
		float mSFXVolume;
	};
}

#endif // WINDATACOMPONENT