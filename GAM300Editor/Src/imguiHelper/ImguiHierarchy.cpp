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

	void Hierarchy::insetOnHoldEntities(EntityID newParent)
	{
		auto found = entitiesInputted.find(newParent);
		if (found != entitiesInputted.end()) // Means its found
		{
			for (auto entity : entitiesOnHold[newParent])
			{
				found->second->children.emplace_back(entity);
				insetOnHoldEntities(entity);
			}
		}
	}

	void Hierarchy::init()
	{
		//auto allEntities = ecs.getEntities();

		//for (EntityID& entity : allEntities)
		//{
		//	if (NameTag* nameTagComponent = ecs.getComponent<NameTag>(entity))
		//	{
		//		EntityID parent = nameTagComponent->GetHierarchyParent();

		//		// Means no parent (parent = 0)
		//		if (!parent)
		//		{
		//			if (hierarchyEntities.size() <= nameTagComponent->GetHierarchyIndex())
		//			{
		//				ImguiHierarchyEntity newHierarchyEntity;
		//				newHierarchyEntity.parent = entity;
		//				hierarchyEntities.emplace_back(newHierarchyEntity);
		//				entitiesInputted[entity] = &hierarchyEntities[hierarchyEntities.size() - 1];

		//				inputEntitiesOnHold(entity);
		//			}
		//			else // Means its in the middle 
		//			{
		//				for (int i = 0; i < hierarchyEntities.size(); ++i)
		//				{
		//					if (ecs.getComponent<NameTag>(hierarchyEntities[i].parent)->GetHierarchyIndex() > nameTagComponent->GetHierarchyIndex())
		//					{
		//						ImguiHierarchyEntity newHierarchyEntity;
		//						newHierarchyEntity.parent = entity;
		//						hierarchyEntities.emplace(hierarchyEntities.begin() + i, newHierarchyEntity);
		//						entitiesInputted[entity] = &hierarchyEntities[i];

		//						inputEntitiesOnHold(entity);
		//						break;
		//					}
		//				}
		//			}
		//		}
		//		else // Will try to find the parent, if cannot find, then put it into on hold
		//		{
		//			//entitiesOnHold
		//			if (parent > entity) // Parent wont be inputted yet
		//			{
		//				entitiesOnHold[parent].emplace_back(entity);
		//			}
		//			else
		//			{
		//				ImguiHierarchyEntity newHierarchyEntity;
		//				newHierarchyEntity.parent = entity;

		//				if ((*entitiesInputted[parent]).children.size() <= nameTagComponent->GetHierarchyIndex())
		//				{
		//					ImguiHierarchyEntity newHierarchyEntity;
		//					newHierarchyEntity.parent = entity;
		//					(*entitiesInputted[parent]).children.emplace_back(newHierarchyEntity);
		//					entitiesInputted[entity] = &entitiesInputted[parent][(*entitiesInputted[parent]).children.size() - 1];
		//				}
		//				else // Means its in the middle 
		//				{
		//					for (int i = 0; i < (*entitiesInputted[parent]).children.size(); ++i)
		//					{
		//						if (ecs.getComponent<NameTag>(entitiesInputted[parent][i].parent)->GetHierarchyIndex() > nameTagComponent->GetHierarchyIndex())
		//						{
		//							ImguiHierarchyEntity newHierarchyEntity;
		//							newHierarchyEntity.parent = entity;
		//							(*entitiesInputted[parent]).children.emplace((*entitiesInputted[parent]).children.begin() + i, newHierarchyEntity);
		//							entitiesInputted[entity] = &entitiesInputted[parent][i];

		//							inputEntitiesOnHold(entity);
		//							break;
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
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