//set up temporary for now till we get the engine out and export our functions 
// then will transfer to gam300editor side

#ifndef TDS_IMGUI_HELPER
#define TDS_IMGUI_HELPER

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_vulkan.h>

#include "components/components.h"

namespace TDS 
{
	enum PanelTypes
	{
		HIERARCHY,
		PROPERTIES,
		//PREFABS,
		//MENUBAR,
		//BEHAVIORTREE,
		ASSETBROWSER
		//BEHAVIOURTREEEDITOR,
		//ANIMATIONBROWSER
		// TILEMAP
		// SOUND
		// ANIMATION
	};

	class LevelEditorPanel
	{
	public:
		virtual void update() = 0;

		std::string panelTitle;
		ImGuiWindowFlags flags;
		ImVec2 windowPadding;
	private:
	};

	class LevelEditorManager
	{
	public:
		static std::unique_ptr<LevelEditorManager>& GetInstance();

		std::map<PanelTypes, std::shared_ptr<LevelEditorPanel>> panels;	// cant be unique pointer for some reason
	private:
		// Unique pointer to SceneManager
		static std::unique_ptr<LevelEditorManager> m_instance;
	};

	namespace imguiHelper
	{
		void InitializeImgui(ImGui_ImplVulkan_InitInfo initinfo, VkRenderPass RenderPass, void* inHwnd);

		void ImguiCreateFont(VkCommandBuffer SingleUseCommandBuffer);

		void Update();

		void Draw(VkCommandBuffer FCB);

		void Exit();
	}

#define IMGUI_WIN32_WNDPROCHANDLER_FORWARD_DECLARATION extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

}

#endif // !TDS_IMGUI_HELPER
