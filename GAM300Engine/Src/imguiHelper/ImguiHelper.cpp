
#include "imguiHelper/ImguiHelper.h"
namespace TDS
{
	void imguiHelper::initializeImgui(ImGui_ImplVulkan_InitInfo initinfo, VkRenderPass RenderPass, void* inHwnd)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io{ ImGui::GetIO() };
		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();
		ImGui_ImplVulkan_Init(&initinfo, RenderPass);
		ImGui_ImplWin32_Init(inHwnd);
	}

	void imguiHelper::createFont(VkCommandBuffer SingleUseCommandBuffer)
	{
		ImGui_ImplVulkan_CreateFontsTexture(SingleUseCommandBuffer);
	}

	void imguiHelper::Update()
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void imguiHelper::Draw(VkCommandBuffer FCB)
	{
		ImGuiIO& io{ ImGui::GetIO() };

		if (const ImGuiViewport* pViewPort{ ImGui::GetMainViewport() }; pViewPort != nullptr)
		{
			io.DisplaySize = pViewPort->Size;
		}
		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), FCB);
	}

	void imguiHelper::Exit()
	{
			ImGui_ImplVulkan_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
	}



}