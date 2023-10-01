/*!*****************************************************************************
 * \file          TextureFactory.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the declaration of the TextureFactory class.
 *******************************************************************************/
#pragma once
#include "FactoryBase.h"
#include "GraphicsResource/TextureInfo.h"
#define TEXTURE_PATH "../assets/textures/"
namespace TDS
{

	template<>
	class DLL_API AssetFactory<Texture>
	{

	private:
		std::unordered_map<std::string, std::int32_t> m_LoadedTexture;
		std::vector<std::uint64_t> m_LoadedTextureGUID;
	public:
		/*!*************************************************************************
		 * Preloading from resource manager
		 ***************************************************************************/
		void Preload(ResourceManager& resourceMgr)
		{
			std::filesystem::path dir = TEXTURE_PATH;

			if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir))
			{
				std::cout << "Invalid directory" << std::endl;
				return;
			}

			for (const auto& entry : std::filesystem::directory_iterator(dir))
			{
				const std::filesystem::path& path = entry.path();
				if (path.extension() == ".dds")
				{
					SingleTypeReference<Texture> TextureInstance{};

					std::string fileName = path.filename().string();
					TextureInstance.m_Identifier.GetTypeName<Texture>();
					TextureInstance.m_Identifier.CreateTypeIDByName(fileName);
					TextureInstance.m_GUID = UniqueID::CreateUniqueGuid();

					auto newTexture = resourceMgr.getResource(TextureInstance);
					if (newTexture == nullptr)
					{
						std::cout << "Failed to get texture instance!" << std::endl;
						continue;
					}
					TextureData loader{};
					loader.LoadTexture(path.string());
					newTexture->LoadTextureData(loader);
					m_LoadedTexture[fileName] = m_LoadedTextureGUID.size();
					m_LoadedTextureGUID.emplace_back(TextureInstance.m_GUID.GetUniqueID());
				}
			}
		}
		/*!*************************************************************************
		 * Load the texture data from TextureData
		 ***************************************************************************/
		static void Load(std::string_view path, SingleTypeReference<Texture>& textureRef, ResourceManager& resourceMgr)
		{
			auto texRef = resourceMgr.getResource(textureRef);
			if (texRef == nullptr)
			{
				std::cout << "Failed to get texture instance!" << std::endl;
				return;
			}
			TextureData loader{};
			loader.LoadTexture(path);
			texRef->LoadTextureData(loader);
		}

	};



}