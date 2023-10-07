/*!*************************************************************************
****
\file ImguiSceneBrowser.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Level Editor Scene Browser
		panel
****************************************************************************
***/

#include "imguiHelper/ImguiSceneBrowser.h"
#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
	/*!*************************************************************************
	This function initializes the Scene Broswer panel
	****************************************************************************/
	SceneBrowser::SceneBrowser()
	{
		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Scene Browser";
		windowPadding = ImVec2(10.f, 10.f);
	}

	/*!*************************************************************************
	This function is the update function for Scene Broswer panel
	****************************************************************************/
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
					ecs.removeAllEntities();
				}
				if (ImGui::MenuItem("Save")) 
				{
					SceneManager::GetInstance()->saveScene(SceneManager::GetInstance()->getCurrentScene());
					SceneManager::GetInstance()->sceneSerialize();
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