/*!*****************************************************************************
 * \file          TextureInfo.cpp
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the implementation of the TextureInfo class.
 *******************************************************************************/
#define TINYDDSLOADER_IMPLEMENTATION
#include "GraphicsResource/TextureInfo.h"

#include <iostream>

namespace TDS
{
	void TextureData::LoadTexture(std::string_view path)
	{
		tinyddsloader::Result result = m_TextureLoaded.Load(path.data());

		if (result != tinyddsloader::Result::Success)
			std::cout << "Failed to load texture" << std::endl;

	}
	void Texture::LoadTextureData(TextureData& textureData)
	{

	}
}