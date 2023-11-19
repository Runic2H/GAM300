#include "GraphicsResource/FontInfo.h"
#include "rapidJSON/document.h"
namespace TDS
{
    void FontAtlas::DeserializeFontAtlas(std::string_view path)
    {
        std::ifstream file(path.data());
        if (!file.is_open())
        {
            //TDS_ERROR("Failed to open {}", path.data());
            return;
        }
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        rapidjson::Document doc;
        doc.Parse(content.c_str());

        // Extracting Atlas related data
        const auto& atlasObj = doc["atlas"];
        m_Atlas.m_Type = atlasObj["type"].GetString();
        m_Atlas.m_DistanceRange = atlasObj["distanceRange"].GetDouble();
        m_Atlas.m_Size = atlasObj["size"].GetDouble();
        m_Atlas.m_Width = atlasObj["width"].GetInt();
        m_Atlas.m_Height = atlasObj["height"].GetInt();
        m_Atlas.yOrigin = atlasObj["yOrigin"].GetString();

        m_Name = doc["name"].GetString();

        // Extracting Metrics related data
        const auto& metricsObj = doc["metrics"];
        m_Metrics.m_emSize = metricsObj["emSize"].GetDouble();
        m_Metrics.m_LineHeight = metricsObj["lineHeight"].GetDouble();
        m_Metrics.m_Ascender = metricsObj["ascender"].GetDouble();
        m_Metrics.m_Descender = metricsObj["descender"].GetDouble();
        m_Metrics.m_UnderlineY = metricsObj["underlineY"].GetDouble();
        m_Metrics.m_UnderlineThickness = metricsObj["underlineThickness"].GetDouble();

        const auto& glyphsArray = doc["glyphs"].GetArray();

        for (const auto& glyphObj : glyphsArray)
        {
            Glyph glyph;
            glyph.m_uniCode = glyphObj["unicode"].GetInt();
            glyph.m_Advance = glyphObj["advance"].GetDouble();

            if (glyphObj.HasMember("planeBounds") && glyphObj["planeBounds"].IsObject())
            {
                const auto& planeBounds = glyphObj["planeBounds"].GetObject();
                glyph.m_PlaneBounds.m_Left = planeBounds["left"].GetDouble();
                glyph.m_PlaneBounds.m_Bottom = planeBounds["bottom"].GetDouble();
                glyph.m_PlaneBounds.m_Right = planeBounds["right"].GetDouble();
                glyph.m_PlaneBounds.m_Top = planeBounds["top"].GetDouble();
            }
            else
            {
                //TDS_ERROR("Glyph unicode {} is missing 'planeBounds'", glyph.m_uniCode);
            }

            if (glyphObj.HasMember("atlasBounds") && glyphObj["atlasBounds"].IsObject())
            {
                const auto& atlasBounds = glyphObj["atlasBounds"].GetObject();
                glyph.m_AtlasBounds.m_Left = atlasBounds["left"].GetDouble();
                glyph.m_AtlasBounds.m_Bottom = atlasBounds["bottom"].GetDouble();
                glyph.m_AtlasBounds.m_Right = atlasBounds["right"].GetDouble();
                glyph.m_AtlasBounds.m_Top = atlasBounds["top"].GetDouble();
            }
            else
            {
                //TDS_ERROR("Glyph unicode {} is missing 'atlasBounds'", glyph.m_uniCode);
                // You can assign default values to m_AtlasBounds here if needed
            }
            char character = static_cast<char>(glyph.m_uniCode);
            m_Glyphs.insert(std::make_pair(character, glyph));
        }



        if (doc.HasMember("kerning") && doc["kerning"].IsArray() && doc["kerning"].Size() > 0)
        {
            const auto& kerningArray = doc["kerning"].GetArray();
            for (const auto& kerningObj : kerningArray)
            {
                int first = kerningObj["first"].GetInt();
                int second = kerningObj["second"].GetInt();
                m_Kerning.emplace_back(first, second);
            }
        }

    }

    bool FontAtlas::DescenderExist(const Glyph& glyph, const Metrics& metrics)
    {
        return glyph.m_PlaneBounds.m_Bottom < metrics.m_Descender;
    }

    bool FontAtlas::AscenderExist(const Glyph& glyph, const Metrics& metrics)
    {
        return glyph.m_PlaneBounds.m_Top > metrics.m_Ascender;
    }


}