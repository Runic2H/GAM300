/*!*************************************************************************
****
\file sprite.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the sprite component class
****************************************************************************
***/

#ifndef SPRITECOMPONENT
#define SPRITECOMPONENT

#include "Vector2.h"
#include "ecs/ecs.h"

namespace TDS
{
	class Sprite : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the Sprite component when created
		****************************************************************************/
		DLL_API Sprite();
		/*!*************************************************************************
		Initializes the Sprite component when created, given another Sprite
		component to move (for ECS)
		****************************************************************************/
		DLL_API Sprite(Sprite&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Sprite component class
		****************************************************************************/
		DLL_API ~Sprite() = default;
		/*!*************************************************************************
		Deserializes the Sprite component
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the Sprite component
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the Sprite component class
		****************************************************************************/
		DLL_API Vec2& GetIndex() { return mIndex; }
		DLL_API void SetIndex(Vec2 index) { mIndex = index; }

		DLL_API bool& GetIsSpriteSheet() { return mIsSpriteSheet; }
		DLL_API void SetIsSpriteSheet(bool isSpriteSheet) { mIsSpriteSheet = isSpriteSheet; }
		
		DLL_API bool& GetIsAnimated() { return mIsAnimated; }
		DLL_API void SetIsAnimated(bool isAnimated) { mIsAnimated = isAnimated; }
		
		DLL_API float& GetInternalTimer() { return mInternalTimer; }
		DLL_API void SetInternalTimer(float internalTimer) { mInternalTimer = internalTimer; }
		
		DLL_API int& GetLayerOrder() { return mLayerOrder; }
		DLL_API void SetLayerOrder(int layerOrder) { mLayerOrder = layerOrder; }
		
		DLL_API std::string& GetTextureName() { return mTextureName; }
		DLL_API void SetTextureName(std::string textureName) { mTextureName = textureName; }
		
		DLL_API Vec2& GetUVcooridnates() { return mUVcooridnates; }
		DLL_API void SetUVcooridnates(Vec2 UVcooridnates) { mUVcooridnates = UVcooridnates; }
		
		DLL_API float& GetAlpha() { return mAlpha; }
		DLL_API void SetAlpha(float alpha) { mAlpha = alpha; }

		DLL_API int& GetMaxIndex() { return mMaxIndex; }
		DLL_API void SetMaxIndex(int maxIndex) { mMaxIndex = maxIndex; }
		
		DLL_API std::vector<float>& GetDisplayTime() { return mDisplayTime; }

		RTTR_ENABLE();
		RTTR_REGISTRATION_FRIEND

	private:
		Vec2 mIndex;

		bool mIsSpriteSheet; // to tell whether we are using a spritesheet
		bool mIsAnimated;	// if is a spritesheet do we want it to be animated 
		float mInternalTimer;
		int mLayerOrder;

		std::string mTextureName;
		Vec2 mUVcooridnates;
		float mAlpha;
		int mMaxIndex;
		std::vector<float> mDisplayTime;
	};
}

#endif // SPRITECOMPONENT