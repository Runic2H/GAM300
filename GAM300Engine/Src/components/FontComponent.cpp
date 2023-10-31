#include "components/FontComponent.h"
#include "vulkanTools/VulkanTexture.h"
namespace TDS
{
	FontComponent::FontComponent() :m_FontInfo{}, m_Color{}
	{
		m_FontInfo.m_FontAtlasTexture = std::make_shared<Texture>();
	}
	FontComponent::FontComponent(FontComponent&& toMove) noexcept :m_UIText(toMove.m_UIText), m_FontInfo(toMove.m_FontInfo), m_Color(toMove.m_Color)
	{
	}
	FontComponent::~FontComponent()
	{
		if (m_FontInfo.m_FontAtlasTexture->m_VulkanTexture != nullptr)
		{
			m_FontInfo.m_FontAtlasTexture->Destroy();
			delete m_FontInfo.m_FontAtlasTexture->m_VulkanTexture;
			m_FontInfo.m_FontAtlasTexture = nullptr;

		}
	}
	DLL_API bool FontComponent::Deserialize(const rapidjson::Value& obj)
	{
		(obj);
		return true;
	}
	DLL_API bool FontComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		(writer);
		return true;
	}
	void FontComponent::LoadFont(std::string_view Path)
	{
		m_FontInfo.m_FontAtlasTexture->LoadTexture(Path);
		m_FontInfo.m_FontAtlasTexture->m_VulkanTexture = new VulkanTexture();
		m_FontInfo.m_FontAtlasTexture->m_TextureInfo.m_UsingMipMaps = false;
		m_FontInfo.m_FontAtlasTexture->m_VulkanTexture->CreateTexture(m_FontInfo.m_FontAtlasTexture->m_TextureInfo);

	}
}