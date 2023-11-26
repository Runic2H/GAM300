#pragma once
#include "sceneManager/sceneManager.h"

namespace ScriptAPI
{
	//Bobo class to load scene
	public ref class SceneLoader
	{
	public:
		static void LoadMainMenu();

		static void LoadMainGame();

		static void LoadStartingCutscene();
	};
}