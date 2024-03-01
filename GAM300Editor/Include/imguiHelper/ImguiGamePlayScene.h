#ifndef IMGUI_GAMEPLAYSCENE
#define IMGUI_GAMEPLAYSCENE

#include "ImguiHelper.h"
#include "imguiHelper/ImguiHierarchy.h"
namespace TDS
{
	class GamePlayScene : public LevelEditorPanel
	{
	public:
		GamePlayScene();

		void init();
		void update();
		void Resize();

		bool isFocus{ false };
		bool isControlling{ false };
	private:
		VkDescriptorSet m_GamePlayDesc{};

		ImVec2 window_size;
		ImVec2 window_pos;

		BOOL show_cursor;
		ImGuiContext* currentContext; // checking is running exe or editor
	};
}

#endif // IMGUI_GAMEPLAYSCENE
