#include "Tools/FontLoader.h"
#include "Tools/FileExtensions.h"
#include <cstdlib>
#include "Tools/TextureCompressor.h"
#include "Tools/DDSConverter.h"
#include "vulkanTools/VulkanTexture.h"
#include "AssetManagement/AssetManager.h"
#define FONT_COMPILER_PATH "../assets/Fonts/FontCompiler/msdf-atlas-gen.exe"
namespace TDS
{
	bool FontLoader::RunFontLoader(LoaderDescriptor& desc, std::string& ddsTexturePath)
	{

		//Get the absolute path of the input file
		std::filesystem::path FontCompilerPath = std::filesystem::absolute(FONT_COMPILER_PATH);

		std::string Command = FontCompilerPath.string();

		Command += " -font ";
		Command += desc.m_InputPath;
		Command += " -fontname ";
		Command += RemoveFileExtension(std::filesystem::path(desc.m_InputPath).filename().string(), ".ttf");
		Command += " -type ";
		Command += "msdf";
		Command += " -format ";
		Command += FormatToString(desc.m_AtlasFormat);
		if (!desc.m_AutoDimension)
		{
			Command += " -dimensions ";
			Command += std::to_string((long double)desc.width);
			Command += " ";
			Command += std::to_string((long double)desc.height);
		}
		Command += " -json ";

		std::string JsonLayout = RemoveFileExtension(std::filesystem::path(desc.OutPath).string(), ".ttf");
		std::string forLayout = JsonLayout;
		JsonLayout = std::filesystem::absolute(JsonLayout).string();
		JsonLayout += "layout.json";
		forLayout += "layout.json";
		Command += JsonLayout;
		Command += " -imageout ";
		std::string bmpFile = RemoveFileExtension(std::filesystem::path(desc.OutPath).string(), ".ttf");
		bmpFile = std::filesystem::absolute(bmpFile).string();

		if (desc.m_AtlasFormat == IMAGE_FORMAT::PNG)
		{
			bmpFile += "image.png";
		}
		else if (desc.m_AtlasFormat == IMAGE_FORMAT::BIN)
		{
			bmpFile += "image.bin";
		}
		Command += bmpFile;
		int result = system(Command.c_str());

		if (result == 0)
		{
			std::string Input = bmpFile;
			std::string output = desc.OutPath;
			output += ".dds";
			DDSConverter::ConvertToDDS(Input, output);
			ddsTexturePath = output;

			return true;
		}

		return false;



	}
	std::string FormatToString(IMAGE_FORMAT format)
	{
		if (format == IMAGE_FORMAT::PNG)
			return std::string("png");
		else if (format == IMAGE_FORMAT::TIFF)
			return std::string("tiff");
		else if (format == IMAGE_FORMAT::BIN)
			return std::string("bin");
	}
}


