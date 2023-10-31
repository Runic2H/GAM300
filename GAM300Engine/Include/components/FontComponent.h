#pragma once

#include "components/iComponent.h"
#include "GraphicsResource/FontInfo.h"
namespace TDS
{
	class FontComponent : public IComponent
	{
	public:

		DLL_API FontComponent();

		DLL_API FontComponent(FontComponent&& toMove) noexcept;

		DLL_API ~FontComponent();

		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);

		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		DLL_API void LoadFont(std::string_view Path);
	public:
		std::string m_UIText = "Hello Testing";

		FontInfo m_FontInfo;

		Color m_Color;

	};
}