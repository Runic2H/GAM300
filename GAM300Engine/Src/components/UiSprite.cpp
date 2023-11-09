#include "components/UiSprite.h"

namespace TDS
{

	RTTR_REGISTRATION
	{
		using namespace TDS;

		rttr::registration::class_<UISprite>("UI Sprite")
			.method("SetPosition", &UISprite::SetPosition)
			.method("GetPosition", &UISprite::GetPosition)
			.method("SetRotation", &UISprite::SetRotation)
			.method("GetRotation", &UISprite::GetRotation)
			.method("GetScale", &UISprite::GetScale)
			.method("SetScale", &UISprite::SetScale)
			.property("Color", &UISprite::m_Color)
			.property("Texture", &UISprite::m_TextureName)
			.property("EnableSprite", &UISprite::m_EnableSprite)
			.property("LayerID", &UISprite::m_LayerID)
			.property("Position", &UISprite::m_Pos)
			.property("Scale", &UISprite::m_Scale)
			.property("Rotation", &UISprite::m_Rotation);
			
			
	}

	UISprite::UISprite():m_TextureReference(), m_LayerID(-1), m_Color(0.1f, 0.1f, 0.1f), m_EnableSprite(true),
		m_TextureName("")
	{
	}
	UISprite::UISprite(UISprite&& toMove) noexcept:
		m_TextureReference(std::move(toMove.m_TextureReference)),
		m_LayerID(std::move(toMove.m_LayerID)),
		m_Color(std::move(toMove.m_Color)),
		m_EnableSprite(std::move(toMove.m_EnableSprite)),
		m_TextureName(std::move(toMove.m_TextureName)),
		m_Pos(std::move(toMove.m_Pos)),
		m_Scale(std::move(toMove.m_Scale)),
		m_Rotation(std::move(toMove.m_Rotation))
	{
		
	}
	void UISprite::SetPosition(Vec3& Position)
	{
		m_Pos = Position;
		m_IsDirty = true;
	}
	void UISprite::SetScale(Vec3& Scale)
	{
		m_Scale = Scale;
		m_IsDirty = true;
	}
	void UISprite::SetRotation(Vec3& Rotation)
	{
		m_Rotation = Rotation;
		m_IsDirty = true;
	}
	Vec3 UISprite::GetPosition()
	{
		return m_Pos;
	}
	Vec3 UISprite::GetScale()
	{
		return m_Scale;
	}
	Vec3 UISprite::GetRotation()
	{
		return m_Rotation;
	}
}