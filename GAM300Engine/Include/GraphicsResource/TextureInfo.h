/*!*****************************************************************************
 * \file          TextureInfo.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Loading of texture using TinyDDS
 *******************************************************************************/
#pragma once
#include <stdarg.h>
#include <vulkan/vulkan.h>
#include "dds/tinyddsloader.h"
#include "dotnet/ImportExport.h"
namespace TDS
{
	/*!*************************************************************************
	 * Loading of texture using TinyDDS
	 ***************************************************************************/
	struct DLL_API TextureData
	{
		tinyddsloader::DDSFile m_TextureLoaded;
		void LoadTexture(std::string_view path);


	};

	struct TextureSettings
	{
		bool m_FlipTextureY = true;
		bool m_UseAnistrophy = true;
	};
	struct DLL_API Texture
	{
		void LoadTextureData(TextureData& textureData);
		VkFormat m_Format;
		VkImageType m_ImageType = VK_IMAGE_TYPE_2D;
		VkSamplerAddressMode m_SampleAddressMode = VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_REPEAT;
		VkBorderColor m_BorderClr = VkBorderColor::VK_BORDER_COLOR_INT_OPAQUE_WHITE;
		VkFilter m_ImageFilter = VkFilter::VK_FILTER_LINEAR;
		std::uint32_t m_Width = 0, m_Height = 0;
		std::uint32_t m_CustomMips = 0;
		std::uint32_t m_Depth = 1;

	};




}