#pragma once
#include "dotnet/ImportExport.h"

namespace TDS
{
	struct Glyph
	{
		struct Bounds
		{
			double m_Left, m_Right, m_Bottom, m_Top;
		};
		int m_uniCode = 0;
		double m_Advance = 1.f;
		Bounds m_PlaneBounds, m_AtlasBounds;
	};

	struct FontAtlas
	{
		struct Atlas
		{
			std::string m_Type;
			double m_DistanceRange;
			double m_Size;
			std::int32_t m_Width, m_Height;
			std::string yOrigin;
		}m_Atlas;

		std::string m_Name;

		struct Metrics
		{
			double m_emSize;
			double m_LineHeight;
			double m_Ascender;
			double m_Descender;
			double m_UnderlineY;
			double m_UnderlineThickness;
		} m_Metrics;

		std::map<char, Glyph> m_Glyphs;
		std::vector<std::pair<int, int>> m_Kerning;

		void DLL_API DeserializeFontAtlas(std::string_view path);
	};
	class Texture;
	struct FontInfo
	{
		std::shared_ptr<Texture> m_FontAtlasTexture = nullptr;
		FontAtlas m_AtlasLayout;
	};






}