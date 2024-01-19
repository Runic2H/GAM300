#include "AssetManagement/AssetManager.h"

namespace TDS
{


	AssetManager::AssetManager()
	{
	}
	AssetManager::~AssetManager()
	{
	}
	void AssetManager::Init()
	{
	}
	void AssetManager::PreloadAssets()
	{
		m_ModelFactory.Preload();
		m_TextureFactory.Preload();
		m_FontFactory.Preload();
	}

	void AssetManager::ShutDown()
	{
		m_ModelFactory.DestroyAllModels();
		m_TextureFactory.DestroyAllTextures();
		m_FontFactory.DestroyAllFonts();

	}

	AssetFactory<AssetModel>& AssetManager::GetModelFactory()
	{
		return m_ModelFactory;
	}

	AssetFactory<Texture>& AssetManager::GetTextureFactory()
	{
		return m_TextureFactory;
	}

	AssetFactory<FontAtlas>& AssetManager::GetFontFactory()
	{
		return m_FontFactory;
	}

	 AssetFactory<MeshController>& AssetManager::GetMeshFactory()
	{
		 return m_MeshFactory;
	}

	std::shared_ptr<AssetManager> AssetManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = std::make_shared<AssetManager>();
		return m_Instance;
	}



}