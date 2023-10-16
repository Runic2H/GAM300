/*!*************************************************************************
****
\file ImguiHierarchy.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Level Editor Hierarchy 
		panel
****************************************************************************
***/

#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
	/*!*************************************************************************
	This function initializes the Hierarchy panel
	****************************************************************************/
	Hierarchy::Hierarchy()
	{
		selectedEntity = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Hierarchy";
		windowPadding = ImVec2(0.f, 0.f);

		//insertEntities();
	}

	/*!*************************************************************************
	This function is the update function for Hierarchy panel
	****************************************************************************/
	void Hierarchy::update()
	{
		if (ImGui::BeginMenuBar())
		{
			// Add entity (make it a menu item if there are prefabs)
			if (ImGui::BeginMenu("Create New | V"))
			{
				if (ImGui::MenuItem("Empty"))
				{
					Entity newEntity;
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					selectedEntity = newEntity.getID();

					TDS_INFO("New Entity Created");
				}
				if (ImGui::MenuItem("Square"))
				{
					// Add Sprite or smth to render a square
					Entity newEntity;
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					selectedEntity = newEntity.getID();

					TDS_INFO("New Entity Created");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGuiTreeNodeFlags nodeFlags =
			ImGuiTreeNodeFlags_DefaultOpen |
			ImGuiTreeNodeFlags_FramePadding |
			ImGuiTreeNodeFlags_SpanAvailWidth |
			ImGuiTreeNodeFlags_SpanFullWidth;

		ImGui::PushID(0);
		if (ImGui::TreeNodeEx(SceneManager::GetInstance()->getCurrentScene().c_str(), nodeFlags))
		{
			for (auto entityID : ecs.getEntities())
			{
				if (NameTag* nameTagComponent = ecs.getComponent<NameTag>(entityID))
				{
					bool itemHovered = false;

					ImGui::PushID(entityID);

					bool selectable = ImGui::Selectable(nameTagComponent->GetNameTag().c_str(), selectedEntity == entityID);
					if (ImGui::IsItemHovered())
					{
						itemHovered = true;
					}
					if (selectable)
					{
						selectedEntity = entityID;
					}

					if (ImGui::BeginPopupContextItem("entityPopup"))
					{
						if (ImGui::Selectable("Remove Entity"))
						{
							ecs.removeEntity(selectedEntity);
							selectedEntity = 0;
						}

						ImGui::EndPopup();
					}

					if (rightClick && itemHovered)
					{
						selectedEntity = entityID;
						ImGui::OpenPopup("componentsPopup");
					}

					ImGui::PopID();
				}
			}
			ImGui::TreePop();
		}
		ImGui::PopID();
	}
}