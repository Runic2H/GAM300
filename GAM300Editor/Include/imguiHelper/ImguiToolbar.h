#ifndef IMGUI_TOOLBAR
#define IMGUI_TOOLBAR

#include "ImguiHelper.h"

namespace TDS 
{
	class Toolbar : public LevelEditorPanel
	{
	public:
		Toolbar();

		void init() {}
		void update();

	private:
		bool isStopped;
		bool isPlay;
		bool isOpenFMOD;
		bool isPause;
		bool isLoadScene;
		bool isSaveScene;

	};
}

#endif // IMGUI_CONSOLE
