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

		anyItemHovered = false;
		popupOpened = false;
	}

	void Hierarchy::init()
	{
		hierarchyMap.clear();
		auto allEntities = ecs.getEntities();

		for (EntityID& entity : allEntities)
		{
			EntityID parentEntity = ecs.getComponent<NameTag>(entity)->GetHierarchyParent();
			int hierarchyIndex = ecs.getComponent<NameTag>(entity)->GetHierarchyIndex();

			hierarchyMap[entity].parent = parentEntity; 
			hierarchyMap[entity].indexInParent = hierarchyIndex;

			bool inserted = false;
			for (int i = 0; i < hierarchyMap[parentEntity].children.size(); ++i)
			{
				NameTag* childEntity = ecs.getComponent<NameTag>(hierarchyMap[parentEntity].children[i]);

				if (childEntity->GetHierarchyIndex() > hierarchyIndex) // Found the slot to insert current entity
				{
					hierarchyMap[parentEntity].children.emplace(hierarchyMap[parentEntity].children.begin() + i, entity);
					inserted = true;

					break;
				}
			}
			if (!inserted)
			{
				hierarchyMap[parentEntity].children.emplace_back(entity);
			}
		}

		filter.Clear();
	}

	void Hierarchy::changeIndexInEntity()
	{
		for (EntityID entity : ecs.getEntities())
		{
			ecs.getComponent<NameTag>(entity)->SetHierarchyIndex(hierarchyMap[entity].indexInParent);
			ecs.getComponent<NameTag>(entity)->SetHierarchyParent(hierarchyMap[entity].parent);
		}
	}

	void Hierarchy::reorderingHierarchy(EntityID payloadEntity, EntityID acceptEntity, bool acceptEntityTreeNode)
	{
		auto& currEntityIDHierarchyInfo = hierarchyMap[acceptEntity];
		auto& payloadEntityIDHierarchyInfo = hierarchyMap[payloadEntity];

		if (searchForChild(payloadEntity, acceptEntity)) // Making sure parent / grandparent cannot be moved to the child
		{
			return;
		}

		if (acceptEntity != payloadEntity &&
			!(currEntityIDHierarchyInfo.parent == payloadEntityIDHierarchyInfo.parent
				&& (currEntityIDHierarchyInfo.indexInParent + 1) == payloadEntityIDHierarchyInfo.indexInParent) || acceptEntityTreeNode)
		{
			if (payloadEntity == currEntityIDHierarchyInfo.parent &&
				payloadEntityIDHierarchyInfo.children.size() - 1 == currEntityIDHierarchyInfo.indexInParent) // check if the payload is the last child of the parent
			{
				return;
			}

			hierarchyMap[payloadEntityIDHierarchyInfo.parent].children.erase(
				hierarchyMap[payloadEntityIDHierarchyInfo.parent].children.begin() + payloadEntityIDHierarchyInfo.indexInParent);

			if (acceptEntityTreeNode) // true means currEntity is a parent and the tree node is open, make it the first child
			{
				hierarchyMap[payloadEntity].parent = acceptEntity;
				hierarchyMap[acceptEntity].children.emplace(hierarchyMap[acceptEntity].children.begin(), payloadEntity);

				for (int index = 0; index < hierarchyMap[acceptEntity].children.size(); ++index)
				{
					hierarchyMap[hierarchyMap[acceptEntity].children[index]].indexInParent = index;
				}
			}
			// Just shifting around without changing parent
			else if (payloadEntityIDHierarchyInfo.parent == currEntityIDHierarchyInfo.parent)
			{
				if (payloadEntityIDHierarchyInfo.indexInParent < currEntityIDHierarchyInfo.indexInParent)
				{
					hierarchyMap[currEntityIDHierarchyInfo.parent].children.emplace(
						hierarchyMap[currEntityIDHierarchyInfo.parent].children.begin() + currEntityIDHierarchyInfo.indexInParent,
						payloadEntity);
				}
				else if (currEntityIDHierarchyInfo.indexInParent + 1 == hierarchyMap[currEntityIDHierarchyInfo.parent].children.size())
				{
					hierarchyMap[currEntityIDHierarchyInfo.parent].children.emplace_back(payloadEntity);
				}
				else
				{
					hierarchyMap[currEntityIDHierarchyInfo.parent].children.emplace(
						hierarchyMap[currEntityIDHierarchyInfo.parent].children.begin() + currEntityIDHierarchyInfo.indexInParent + 1,
						payloadEntity);
				}
			}
			else // Different parent
			{
				for (int index = 0; index < hierarchyMap[payloadEntityIDHierarchyInfo.parent].children.size(); ++index)
				{
					hierarchyMap[hierarchyMap[payloadEntityIDHierarchyInfo.parent].children[index]].indexInParent = index;
				}

				payloadEntityIDHierarchyInfo.parent = currEntityIDHierarchyInfo.parent;
				hierarchyMap[currEntityIDHierarchyInfo.parent].children.emplace(hierarchyMap[currEntityIDHierarchyInfo.parent].children.begin() + hierarchyMap[acceptEntity].indexInParent + 1, payloadEntity);
			}

			for (int index = 0; index < hierarchyMap[currEntityIDHierarchyInfo.parent].children.size(); ++index)
			{
				hierarchyMap[hierarchyMap[currEntityIDHierarchyInfo.parent].children[index]].indexInParent = index;
			}
		}
	}

	void Hierarchy::makingChildHierarchy(EntityID payloadEntity, EntityID acceptEntity)
	{
		auto& currEntityIDHierarchyInfo = hierarchyMap[acceptEntity];
		auto& payloadEntityIDHierarchyInfo = hierarchyMap[payloadEntity];

		if (currEntityIDHierarchyInfo.parent != payloadEntity)
		{
			if (searchForChild(payloadEntity, acceptEntity)) // Making sure parent / grandparent cannot be moved to the child
			{
				return;
			}

			hierarchyMap[payloadEntityIDHierarchyInfo.parent].children.erase(
				hierarchyMap[payloadEntityIDHierarchyInfo.parent].children.begin() + payloadEntityIDHierarchyInfo.indexInParent);

			for (int index = 0; index < hierarchyMap[payloadEntityIDHierarchyInfo.parent].children.size(); ++index)
			{
				hierarchyMap[hierarchyMap[payloadEntityIDHierarchyInfo.parent].children[index]].indexInParent = index;
			}

			payloadEntityIDHierarchyInfo.parent = acceptEntity;
			currEntityIDHierarchyInfo.children.emplace_back(payloadEntity);

			for (int index = 0; index < hierarchyMap[acceptEntity].children.size(); ++index)
			{
				hierarchyMap[hierarchyMap[acceptEntity].children[index]].indexInParent = index;
			}
		}
	}

	bool Hierarchy::searchForChild(EntityID parentEntity, EntityID entityToFind)
	{
		for (auto childEntity : hierarchyMap[parentEntity].children)
		{
			if (childEntity == entityToFind)
			{
				return true;
			}
			if (hierarchyMap[childEntity].children.size())
			{
				return searchForChild(childEntity, entityToFind);
			}
		}
		return false;
	}

	void Hierarchy::drawHierarchy(EntityID entityID)
	{
		ImGuiTreeNodeFlags nodeFlags =
			ImGuiTreeNodeFlags_DefaultOpen |
			ImGuiTreeNodeFlags_FramePadding |
			ImGuiTreeNodeFlags_SpanFullWidth | 
			ImGuiTreeNodeFlags_OpenOnArrow;

		ImGui::PushID(entityID);
		bool selected = false;

		// Get Name Tag component
		NameTag* nameTagComponent = ecs.getComponent<NameTag>(entityID);

		// Checking if entity has children
		if (!hierarchyMap[entityID].children.size()) // No children
		{
			ImGui::Indent();

			// Entity will be a selectable as there are no children
			bool currentItemHovered = false;
			selected = ImGui::Selectable(nameTagComponent->GetName().c_str(), selectedEntity == entityID, ImGuiSelectableFlags_SpanAllColumns);

			if (ImGui::IsItemHovered())
			{
				anyItemHovered = true;
				currentItemHovered = true;
			}
			if (ImGui::BeginDragDropSource())
			{
				ImGui::SetDragDropPayload("draggedEntity", &entityID, sizeof(int));
				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("draggedEntity"))
				{
					// Making into child
					EntityID payloadEntityID = *(static_cast<EntityID*>(payload->Data));

					makingChildHierarchy(payloadEntityID, entityID);
				}
				ImGui::EndDragDropTarget();
			}
			if (selected)
			{
				selectedEntity = entityID;
			}

			if (ImGui::BeginPopupContextItem())
			{
				selectedEntity = entityID;
				popupOpened = true;
				if (ImGui::Selectable("Remove Entity"))
				{
					ecs.removeEntity(selectedEntity);
					hierarchyMap[hierarchyMap[selectedEntity].parent].children.erase(
						std::find(hierarchyMap[hierarchyMap[selectedEntity].parent].children.begin(), 
								  hierarchyMap[hierarchyMap[selectedEntity].parent].children.end(), selectedEntity));
					hierarchyMap.erase(selectedEntity);
					selectedEntity = 0;
				}

				ImGui::EndPopup();
			}

			ImGui::Unindent();

			ImGui::PopID();

			ImGui::Separator();
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("draggedEntity"))
				{
					EntityID payloadEntityID = *(static_cast<EntityID*>(payload->Data));

					// Reordering
					reorderingHierarchy(payloadEntityID, entityID);
				}
				ImGui::EndDragDropTarget();
			}

			return;
		}

		// Means there are children
		if (selectedEntity == entityID)
		{
			nodeFlags |= ImGuiTreeNodeFlags_Selected;
		}

		bool currentItemHovered = false;
		selected = ImGui::TreeNodeEx(nameTagComponent->GetName().c_str(), nodeFlags);

		if (ImGui::IsItemHovered())
		{
			anyItemHovered = true;
			currentItemHovered = true;
		}
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("draggedEntity", &entityID, sizeof(int));
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("draggedEntity"))
			{
				// Making into child
				EntityID payloadEntityID = *(static_cast<EntityID*>(payload->Data));

				makingChildHierarchy(payloadEntityID, entityID);
			}
			ImGui::EndDragDropTarget();
		}
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && currentItemHovered)
		{
			selectedEntity = entityID;
		}

		if (ImGui::BeginPopupContextItem())
		{
			selectedEntity = entityID;
			popupOpened = true;
			if (ImGui::Selectable("Remove Entity"))
			{
				ecs.removeEntity(selectedEntity);
				hierarchyMap.erase(selectedEntity);
				selectedEntity = 0;
			}

			ImGui::EndPopup();
		}

		ImGui::PopID();

		ImGui::Separator();
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("draggedEntity"))
			{
				EntityID payloadEntityID = *(static_cast<EntityID*>(payload->Data));

				// Reordering
				reorderingHierarchy(payloadEntityID, entityID, selected);
			}
			ImGui::EndDragDropTarget();
		}

		if (selected)
		{
			std::uint32_t originalSize = hierarchyMap[entityID].children.size();
			for (auto childEntity : hierarchyMap[entityID].children)
			{
				drawHierarchy(childEntity);

				if (originalSize != hierarchyMap[entityID].children.size())
				{
					ImGui::TreePop();

					return;
				}
			}
			ImGui::TreePop();
		}
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
					EntityID newEntityID = newEntity.getID();
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					selectedEntity = newEntityID;

					hierarchyMap[newEntityID].parent = 0;
					hierarchyMap[newEntityID].indexInParent = hierarchyMap[0].children.size();
					hierarchyMap[0].children.emplace_back(newEntityID);

					TDS_INFO("New Entity Created");
				}
				if (ImGui::MenuItem("Square"))
				{
					// Add Sprite or smth to render a square
					Entity newEntity;
					EntityID newEntityID = newEntity.getID();
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					selectedEntity = newEntityID;

					hierarchyMap[newEntityID].parent = 0;
					hierarchyMap[newEntityID].indexInParent = hierarchyMap[0].children.size();
					hierarchyMap[0].children.emplace_back(newEntityID);

					TDS_INFO("New Entity Created");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGuiTreeNodeFlags nodeFlags =
			ImGuiTreeNodeFlags_DefaultOpen |
			ImGuiTreeNodeFlags_FramePadding |
			ImGuiTreeNodeFlags_SpanFullWidth | 
			ImGuiTreeNodeFlags_OpenOnArrow;

		anyItemHovered = false;
		popupOpened = false;

		filter.Draw("##filter");
		ImGui::SameLine();
		if (ImGui::Button("Clear", ImVec2(-FLT_MIN, 0)))
		{
			filter.Clear();
		}
		if (filter.InputBuf[0] == 0)
		{
			if (ImGui::TreeNodeEx(SceneManager::GetInstance()->getCurrentScene().c_str(), nodeFlags))
			{
				ImGui::Separator();
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("draggedEntity"))
					{
						EntityID payloadEntityID = *(static_cast<EntityID*>(payload->Data));

						// Reordering
						reorderingHierarchy(payloadEntityID, 0, true);
					}
					ImGui::EndDragDropTarget();
				}

				std::uint32_t originalSize = hierarchyMap[0].children.size();
				for (auto childEntity : hierarchyMap[0].children)
				{
					drawHierarchy(childEntity);

					if (originalSize != hierarchyMap[0].children.size())
					{
						ImGui::TreePop();
						return;
					}
				}
				ImGui::TreePop();
			}
		}
		else
		{
			for (EntityID entityID : ecs.getEntities())
			{
				NameTag* nameTagComponent = ecs.getComponent<NameTag>(entityID);
				if (filter.PassFilter(nameTagComponent->GetName().c_str()))
				{
					ImGui::PushID(entityID);
					bool selected = false;

					ImGui::Indent();

					// Entity will be a selectable as there are no children
					bool currentItemHovered = false;
					selected = ImGui::Selectable(nameTagComponent->GetName().c_str(), selectedEntity == entityID, ImGuiSelectableFlags_SpanAllColumns);

					if (ImGui::IsItemHovered())
					{
						anyItemHovered = true;
						currentItemHovered = true;
					}
					if (selected)
					{
						selectedEntity = entityID;
					}

					if (ImGui::BeginPopupContextItem())
					{
						selectedEntity = entityID;
						popupOpened = true;
						if (ImGui::Selectable("Remove Entity"))
						{
							ecs.removeEntity(selectedEntity);
							hierarchyMap[hierarchyMap[selectedEntity].parent].children.erase(
								std::find(hierarchyMap[hierarchyMap[selectedEntity].parent].children.begin(),
									hierarchyMap[hierarchyMap[selectedEntity].parent].children.end(), selectedEntity));
							hierarchyMap.erase(selectedEntity);
							selectedEntity = 0;
						}

						ImGui::EndPopup();
					}

					ImGui::Unindent();

					ImGui::PopID();
				}
			}
		}

		if (ImGui::IsWindowHovered() && !popupOpened && !anyItemHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			selectedEntity = 0;
		}
	}
}