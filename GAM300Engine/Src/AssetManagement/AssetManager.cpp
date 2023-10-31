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
		m_ModelFactory.Preload(m_ResourceAllocator);
		m_TextureFactory.Preload(m_ResourceAllocator);
	}

	void DLL_API AssetManager::ShutDown()
	{
		m_ResourceAllocator.FreeAllResources();
	}

	std::shared_ptr<AssetManager> AssetManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = std::make_shared<AssetManager>();
		return m_Instance;
	}



}