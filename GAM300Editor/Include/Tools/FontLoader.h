#pragma once
#include "components/FontComponent.h"
namespace TDS
{

	enum class IMAGE_FORMAT
	{
		PNG, TIFF, BIN
	};


	struct LoaderDescriptor
	{
		std::string m_InputPath{""};
		IMAGE_FORMAT m_AtlasFormat = IMAGE_FORMAT::PNG;
		std::uint32_t width = 100, height = 100;
		bool m_AutoDimension = true;
		std::string OutPath{""};
		std::int32_t m_PixelRange = 2;
		double m_Angle = 4.f;


	};

	std::string FormatToString(IMAGE_FORMAT format);

	namespace FontLoader
	{
		bool RunFontLoader(LoaderDescriptor& desc, FontComponent& font);
	}
}