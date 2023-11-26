#include "SceneLoader.hxx"
#include "TypeConversion.hxx"
#include "EngineInterface.hxx"
namespace ScriptAPI
{
	void SceneLoader::LoadMainMenu()
	{
		EngineInterface::Reload();
		TDS::SceneManager::GetInstance()->loadScene("Main Menu");
	}
	void SceneLoader::LoadMainGame()
	{
		EngineInterface::Reload();
		TDS::SceneManager::GetInstance()->loadScene("Development Game (2)");
	}

	void SceneLoader::LoadStartingCutscene() 
	{
		EngineInterface::Reload();
		TDS::SceneManager::GetInstance()->loadScene("Starting Cutscene");
	}

}