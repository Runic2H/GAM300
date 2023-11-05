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
	private:
		VkDescriptorSet m_GamePlayDesc{};
	};
}

#endif // IMGUI_GAMEPLAYSCENE
