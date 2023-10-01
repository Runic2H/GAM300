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
	class DLL_API Sprite : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the Sprite component when created
		****************************************************************************/
		Sprite();
		/*!*************************************************************************
		Initializes the Sprite component when created, given another Sprite
		component to move (for ECS)
		****************************************************************************/
		Sprite(Sprite&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Sprite component class
		****************************************************************************/
		~Sprite() = default;
		/*!*************************************************************************
		Deserializes the Sprite component
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the Sprite component
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the Sprite component class
		****************************************************************************/
		Vec2& GetIndex() { return mIndex; }
		void SetIndex(Vec2 index) { mIndex = index; }

		bool& GetIsSpriteSheet() { return mIsSpriteSheet; }
		void SetIsSpriteSheet(bool isSpriteSheet) { mIsSpriteSheet = isSpriteSheet; }
		
		bool& GetIsAnimated() { return mIsAnimated; }
		void SetIsAnimated(bool isAnimated) { mIsAnimated = isAnimated; }
		
		float& GetInternalTimer() { return mInternalTimer; }
		void SetInternalTimer(float internalTimer) { mInternalTimer = internalTimer; }
		
		int& GetLayerOrder() { return mLayerOrder; }
		void SetLayerOrder(int layerOrder) { mLayerOrder = layerOrder; }
		
		std::string& GetTextureName() { return mTextureName; }
		void SetTextureName(std::string textureName) { mTextureName = textureName; }
		
		Vec2& GetUVcooridnates() { return mUVcooridnates; }
		void SetUVcooridnates(Vec2 UVcooridnates) { mUVcooridnates = UVcooridnates; }
		
		float& GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

		int& GetMaxIndex() { return mMaxIndex; }
		void SetMaxIndex(int maxIndex) { mMaxIndex = maxIndex; }
		
		std::vector<float>& GetDisplayTime() { return mDisplayTime; }
		
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