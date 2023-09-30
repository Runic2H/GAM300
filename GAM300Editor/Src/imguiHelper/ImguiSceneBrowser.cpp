#include "imguiHelper/ImguiSceneBrowser.h"
#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
	SceneBrowser::SceneBrowser()
	{
		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Scene Browser";
		windowPadding = ImVec2(10.f, 10.f);
	}

	void SceneBrowser::update()
	{
		std::shared_ptr<Hierarchy> hierarchyPanel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[PanelTypes::HIERARCHY]);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
				if (ImGui::MenuItem("New")) 
				{
					SceneManager::GetInstance()->newScene("NewScene");
				}
				if (ImGui::MenuItem("Save")) 
				{
					SceneManager::GetInstance()->saveScene(SceneManager::GetInstance()->getCurrentScene());
				}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

		for (std::string& scene : SceneManager::GetInstance()->getScenes())
		{
			if (ImGui::Button(scene.c_str()) && scene != SceneManager::GetInstance()->getCurrentScene())
			{
				hierarchyPanel->setSelectedEntity(0);
				SceneManager::GetInstance()->loadScene(scene);
			}
			ImGui::SameLine();
		}
	}
}