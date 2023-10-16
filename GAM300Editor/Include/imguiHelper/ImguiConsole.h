#ifndef IMGUI_CONSOLE
#define IMGUI_CONSOLE

#include "ImguiHelper.h"

namespace TDS 
{
	class EditorConsole : public LevelEditorPanel
	{
	public:
		EditorConsole();

		void ClearLog();

		void AddLog(const char* fmt, ...) IM_FMTARGS(2);

		void update();

	private:
		ImVector<char*>       Items;

	};
}

#endif // IMGUI_CONSOLE
