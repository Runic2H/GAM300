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
		m_ResourceManager.RegisterTypes<AssetModel, Texture>();
	}
	void AssetManager::PreloadAssets()
	{
		m_ModelFactory.Preload(m_ResourceManager);
		m_TextureFactory.Preload(m_ResourceManager);
	}

}