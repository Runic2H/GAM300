#include "imguiHelper/ImguiScene.h"
#include "imguiHelper/ImguiAssetBrowser.h"
#include "GraphicsResource/TextureInfo.h"
#include "vulkanTools/VulkanTexture.h"
#include <sstream>
#include <corecrt_wstring.h>
#include "imguiHelper/ImguiConsole.h"

namespace TDS
{
	Texture data{};
	VulkanTexture vkTexture{};
	std::shared_ptr<EditorConsole> consolelog = static_pointer_cast<EditorConsole>(LevelEditorManager::GetInstance()->panels[PanelTypes::CONSOLE]);

	EditorScene::EditorScene()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Scene";
		windowPadding = ImVec2(0.f, 0.f);
		
	}

	std::string tempPath = "../../assets/textures/texture.dds";
	void EditorScene::update()
	{
		//ImGui::Image(reinterpret_cast<void*>(vkTexture.m_DescSet), ImVec2{ 200, 200 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		//if (ImGui::BeginDragDropTarget())
		//{
		//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
		//	{
		//		const wchar_t* path = (const wchar_t*)payload->Data;
		//		std::wstring ws(path);
		//		// your new String
		//		std::string str(ws.begin(), ws.end());
		//		const std::filesystem::path filesystempath = str;

		//		if (filesystempath.extension() != ".dds")
		//		{
		//			consolelog->AddLog("Invalid file type, please select a .DDS file.");
		//		}
		//		else
		//		{
		//			tempPath = str;
		//			std::wcout << " Path is: " << path << std::endl;

		//			//currently i am only changing filepath names, next time i need to impose pictures onto pictures, create new image layer 
		//			//and also parse each image's width and height, rn its hardcoded to 500 x 500 px
		//			/*tempPath = path;
		//			data.LoadTexture(tempPath);
		//			vkTexture.CreateBasicTexture(data.m_TextureInfo);*/

		//		}
		//	}
		//	ImGui::EndDragDropTarget();
		//}
		//data.LoadTexture(tempPath);
		//vkTexture.CreateBasicTexture(data.m_TextureInfo);
		//vkTexture.m_DescSet = ImGui_ImplVulkan_AddTexture(vkTexture.getInfo().sampler, vkTexture.getInfo().imageView, vkTexture.getInfo().imageLayout);

		//code above is currently commented out due to how images are infinitely rendered in update loop and not freed, just for testing

		ImGui::Text("comment out update() in \n ImguiScene.cpp to test dragdrop");
		ImGui::Text("The Image above tests \n Drag and Drop of .dds files");
		ImGui::Text("Drag a .dds file from the \n content browser on the left and drop onto the image");
		ImGui::Text("xx u can render the frame \n buffer here to replace the ImGui::Image");
		ImGui::Text("so in future we will drag \n and rendering multiple images onto the scene");


	}
}