#include "components/UiSprite.h"

namespace TDS
{

	RTTR_REGISTRATION
	{
		using namespace TDS;

	rttr::registration::class_<UISprite>("UI Sprite")
		.property("Color", &UISprite::m_Color)
		.property("Texture", &UISprite::m_TextureName)
		.property("EnableSprite", &UISprite::m_EnableSprite)
		.property("LayerID", &UISprite::m_LayerID)
		.property("is Font", &UISprite::m_IsFont)
		.property("message", &UISprite::m_Message)
		.property("Font Texture", &UISprite::m_FontName)
		.property("ForeGroundColour", &UISprite::m_ForeGroundColour)
		.property("BackGroundColour", &UISprite::m_BackGroundColour);
			
	}

	UISprite::UISprite():
		m_TextureReference(), 
		m_LayerID(-1), 
		m_Color(0.1f, 0.1f, 0.1f), 
		m_EnableSprite(true),
		m_TextureName(""),
		m_Message(""),
		m_BackGroundColour(0.f, 0.f, 0.f, 1.f),
		m_ForeGroundColour(0.f, 0.f, 0.f, 0.f)

	{
	}
	UISprite::UISprite(UISprite&& toMove) noexcept :
		m_TextureReference(std::move(toMove.m_TextureReference)),
		m_LayerID(std::move(toMove.m_LayerID)),
		m_Color(std::move(toMove.m_Color)),
		m_EnableSprite(std::move(toMove.m_EnableSprite)),
		m_TextureName(std::move(toMove.m_TextureName)),
		m_Message(std::move(toMove.m_Message)),
		m_BackGroundColour(std::move(toMove.m_BackGroundColour)),
		m_ForeGroundColour(std::move(toMove.m_ForeGroundColour))
	{
		
	}

}