#pragma once
#include "ecs/ecs.h"
#include "ResourceManagement/ResourceManager.h"
#include "GraphicsResource/FontInfo.h"
#include "ResourceManagement/ResourceRef.h"
namespace TDS
{
	class Texture;
	class UISprite : public IComponent
	{
	public:
		DLL_API UISprite();
		DLL_API UISprite(UISprite&& toMove) noexcept;
		DLL_API ~UISprite() = default;
		inline TypeReference<Texture>& GetReference()
		{
			return m_TextureReference;
		}
		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND
	private:
		TypeReference<Texture>			m_TextureReference;
		TypeReference<FontAtlas>		m_FontReference{};
	public:
		bool							m_IsDirty = false;
		bool							m_EnableSprite = true;
		bool							m_IsFont = false;
		int								m_LayerID = -1;
		Vec4							m_Color;
		std::string						m_TextureName = "";
	public:
		//If is font data
		inline TypeReference<FontAtlas>& GetFontReference()
		{
			return m_FontReference;
		}
		std::string						m_Message = "Hello Testing";
		std::string						m_FontName = "";
		Vec4							m_BackGroundColour = { 0.f, 0.f, 0.f, 0.f };
		Vec4							m_ForeGroundColour = { 0.f, 0.f, 0.f, 0.f };

	};
}