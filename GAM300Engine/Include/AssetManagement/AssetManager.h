#pragma once
#include "AssetManagement/ModelFactory.h"
#include "TextureFactory.h"
#include "dotnet/ImportExport.h"
#include "ResourceAllocator.h"

namespace TDS
{



	class AssetManager
	{
	public:
		DLL_API AssetManager();
		DLL_API ~AssetManager();
		void DLL_API Init();
		void DLL_API PreloadAssets();
		void DLL_API ShutDown();

		//Runtime load
		template <typename T>
		void LoadAsset(std::string_view FilePath, TypeReference<T>& ref)
		{
			AssetFactory<T>::Load(FilePath, ref, m_ResourceAllocator);
		}

		template <typename T>
		T* GetResource(TypeReference<T>& ref)
		{
			return m_ResourceAllocator.GetResource(ref);
		}

		AssetFactory<AssetModel>& GetModelFactory()
		{
			return m_ModelFactory;
		}

		AssetFactory<Texture>& GetTextureFactory()
		{
			return m_TextureFactory;
		}

		inline ResourceAllocator& getResourceAllocator()
		{
			return m_ResourceAllocator;
		}
		static DLL_API std::shared_ptr<AssetManager> GetInstance();


	private:
		inline static std::shared_ptr<AssetManager> m_Instance = nullptr;
		/*ResourceManager m_ResourceManager;*/
		ResourceAllocator m_ResourceAllocator;
		AssetFactory<AssetModel> m_ModelFactory;
		AssetFactory<Texture> m_TextureFactory;


	};
}