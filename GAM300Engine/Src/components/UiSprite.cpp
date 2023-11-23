#include "components/UiSprite.h"

namespace TDS
{

	RTTR_REGISTRATION
	{
		using namespace TDS;

	rttr::registration::class_<UISprite>("UI Sprite")
		.property("Texture", &UISprite::m_TextureName)
		.property("EnableSprite", &UISprite::m_EnableSprite)
		.property("LayerID", &UISprite::m_LayerID)
		.property("is Font", &UISprite::m_IsFont)
		.property("message", &UISprite::m_Message)
		.property("Font Texture", &UISprite::m_FontName)
		.property("ForeGroundColour", &UISprite::m_ForeGroundColour)
		.property("Sprite Color", &UISprite::m_Color)
		.property("BackGroundColour", &UISprite::m_BackGroundColour)
		.property("BoundingBoxMin", &UISprite::m_BoundingBoxMin)
		.property("BoundingBoxMax", &UISprite::m_BoundingBoxMax);

	}

		UISprite::UISprite() :
		m_TextureReference(),
		m_LayerID(-1),
		m_Color(0.1f, 0.1f, 0.1f),
		m_EnableSprite(true),
		m_TextureName(""),
		m_Message(""),
		m_BackGroundColour(0.f, 0.f, 0.f, 1.f),
		m_ForeGroundColour(0.f, 0.f, 0.f, 0.f),
		m_BoundingBoxMin(-0.5f, -0.5f),
		m_BoundingBoxMax(0.5f, 0.5f)

	{
	}
	UISprite::UISprite(UISprite&& toMove) noexcept :
		m_TextureReference(toMove.m_TextureReference),
		m_LayerID(toMove.m_LayerID),
		m_Color(toMove.m_Color),
		m_EnableSprite(toMove.m_EnableSprite),
		m_TextureName(toMove.m_TextureName),
		m_Message(toMove.m_Message),
		m_BackGroundColour(toMove.m_BackGroundColour),
		m_ForeGroundColour(toMove.m_ForeGroundColour),
		m_BoundingBoxMin(toMove.m_BoundingBoxMin),
		m_BoundingBoxMax(toMove.m_BoundingBoxMax)
	{
		
	}

}