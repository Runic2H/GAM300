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
		m_MeshFactory.Preload();
		m_TextureFactory.Preload();
		m_FontFactory.Preload();
	}

	void AssetManager::ShutDown()
	{
		m_MeshFactory.DestroyAllMesh();
		m_TextureFactory.DestroyAllTextures();
		m_FontFactory.DestroyAllFonts();

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