#pragma once
#include "FactoryBase.h"
#include "../GraphicsResource/TextureInfo.h"
#define MAX_NUM_PRELOAD_TEXTURE 10
#define TEXTURE_PATH "../assets/textures/"
namespace TDS
{

	template<>
	class AssetFactory<Texture>
	{

	public:

		void Preload(ResourceAllocator& resourceMgr)
		{
			std::uint32_t NumOfLoadedTexture = 0;
			std::filesystem::path dir = TEXTURE_PATH;

			if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir))
			{
				std::cout << "Invalid directory" << std::endl;
				return;
			}

			for (const auto& entry : std::filesystem::directory_iterator(dir))
			{
				if (NumOfLoadedTexture >= MAX_NUM_PRELOAD_TEXTURE)
					break;
				const std::filesystem::path& path = entry.path();
				if (path.extension() == ".dds")
				{
					TypeReference<Texture> TextureInstance{};

					std::string fileName = path.filename().string();

					TextureInstance.m_AssetName = fileName;

					auto newTexture = resourceMgr.LoadResource(TextureInstance);
					if (newTexture == nullptr)
					{
						std::cout << "Failed to get texture instance!" << std::endl;
						continue;
					}
					newTexture->LoadTexture(path.string());
				}
			}
		}
		static void Load(std::string_view path, TypeReference<Texture>& textureRef, ResourceAllocator& resourceMgr)
		{
			std::filesystem::path FilePath(path);
			std::string fileName = FilePath.filename().string();
			textureRef.m_AssetName = fileName;
			if (!resourceMgr.GetResource(textureRef))
			{
				if (!resourceMgr.LoadResource(textureRef))
				{
					TDS_WARN("Failed to load resource!");
					return;
				}
			}
			textureRef.m_ResourcePtr->LoadTexture(path);
		}

	};



}