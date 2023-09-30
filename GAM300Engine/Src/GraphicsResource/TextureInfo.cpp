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