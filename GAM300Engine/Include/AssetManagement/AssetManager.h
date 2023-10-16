#pragma once
#include <mutex>
#include <memory>
#include "AssetManagement/ModelFactory.h"
#include "TextureFactory.h"
#include "dotnet/ImportExport.h"
namespace TDS
{
	class AssetManager
	{
	public:
		DLL_API AssetManager();
		DLL_API ~AssetManager();
		void DLL_API Init();
		void DLL_API PreloadAssets();

		//Runtime load
		template <typename T>
		void LoadAsset(std::string_view FilePath, SingleTypeReference<T>& ref)
		{
			AssetFactory<T>::Load(FilePath, ref, this->m_ResourceManager);
		}
		AssetFactory<AssetModel>& GetModelFactory()
		{
			return m_ModelFactory;
		}

		AssetFactory<Texture>& GetTextureFactory()
		{
			return m_TextureFactory;
		}
		inline ResourceManager& getResourceManager()
		{
			return m_ResourceManager;
		}
	private:
		ResourceManager m_ResourceManager;
		AssetFactory<AssetModel> m_ModelFactory;
		AssetFactory<Texture> m_TextureFactory;

	};
}