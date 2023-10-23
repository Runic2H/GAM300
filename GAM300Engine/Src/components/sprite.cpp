/*!*************************************************************************
****
\file sprite.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Sprite component class
****************************************************************************
***/

#include "components/sprite.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<Sprite>("Sprite");
}
namespace TDS
{
	/*!*************************************************************************
	Initializes the Sprite component when created
	****************************************************************************/
	Sprite::Sprite() : mIndex			(Vec2(1.0f, 1.0f)),
					   mIsSpriteSheet	(false),
					   mIsAnimated		(false),
					   mInternalTimer	(0.0f),
					   mLayerOrder		(0),
					   mTextureName		("none"),
					   mUVcooridnates	(Vec2(0.0f, 0.0f)),
					   mAlpha			(1.0f),
					   mMaxIndex		(1)
	{ }

	/*!*************************************************************************
	Initializes the Sprite component when created, given another Sprite
	component to move (for ECS)
	****************************************************************************/
	Sprite::Sprite(Sprite&& toMove) noexcept : mIndex			(toMove.mIndex),
											   mIsSpriteSheet	(toMove.mIsSpriteSheet),
											   mIsAnimated		(toMove.mIsAnimated),
											   mInternalTimer	(toMove.mInternalTimer),
											   mLayerOrder		(toMove.mLayerOrder),
											   mTextureName		(toMove.mTextureName),
											   mUVcooridnates	(toMove.mUVcooridnates),
											   mAlpha			(toMove.mAlpha),
											   mMaxIndex		(toMove.mMaxIndex)
	{ }
}
