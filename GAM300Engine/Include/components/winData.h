/*!*************************************************************************
****
\file winData.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the winData component class
****************************************************************************
***/

#ifndef WINDATACOMPONENT
#define WINDATACOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class WinData : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the WinData component when created
		****************************************************************************/
		DLL_API WinData();
		/*!*************************************************************************
		Initializes the WinData component when created, given another WinData
		component to move (for ECS)
		****************************************************************************/
		DLL_API WinData(WinData&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the WinData component class
		****************************************************************************/
		DLL_API ~WinData() = default;
		/*!*************************************************************************
		Deserializes the WinData component
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the WinData component
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the WinData component class
		****************************************************************************/
		DLL_API std::string GetTitle() { return mTitle; }
		DLL_API void SetTitle(std::string title) { mTitle = title; }

		DLL_API std::uint32_t GetWidth() { return mWidth; }
		DLL_API void SetWidth(std::uint32_t width) { mWidth = width; }

		DLL_API std::uint32_t GetHeight() { return mHeight; }
		DLL_API void SetHeight(std::uint32_t height) { mHeight = height; }

		DLL_API std::uint32_t GetCurrentWidth() { return mCurrentWidth; }
		DLL_API void SetCurrentWidth(std::uint32_t currentWidth) { mCurrentWidth = currentWidth; }

		DLL_API std::uint32_t GetCurrentHeight() { return mCurrentHeight; }
		DLL_API void SetCurrentHeight(std::uint32_t currentHeight) { mCurrentHeight = currentHeight; }
		
		DLL_API float GetMasterVolume() { return mMasterVolume; }
		DLL_API void SetMasterVolume(float masterVolume) { mMasterVolume = masterVolume; }
		
		DLL_API float GetBGMVolume() { return mBGMVolume; }
		DLL_API void SetBGMVolume(float BGMVolume) { mBGMVolume = BGMVolume; }
		
		DLL_API float GetSFXVolume() { return mSFXVolume; }
		DLL_API void SetSFXVolume(float SFXVolume) { mSFXVolume = SFXVolume; }

		RTTR_ENABLE();
		RTTR_REGISTRATION_FRIEND

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