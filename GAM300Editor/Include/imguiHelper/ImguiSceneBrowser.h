#ifndef IMGUI_SCENE_BROWSER
#define IMGUI_SCENE_BROWSER

#include <filesystem>

#include "sceneManager/sceneManager.h"
#include "ImguiHelper.h"

namespace TDS 
{
	class SceneBrowser : public LevelEditorPanel
	{
	public:
		SceneBrowser();

		void update();

	private:
	};
}

#endif // IMGUI_SCENE_BROWSER
