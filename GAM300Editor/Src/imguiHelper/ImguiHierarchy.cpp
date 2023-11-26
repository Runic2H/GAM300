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
		hierarchyList.clear();
		auto allEntities = ecs.getEntities();

		for (EntityID& entity : allEntities)
		{
			NameTag* nameTagComponent = ecs.getComponent<NameTag>(entity);
			if (nameTagComponent->GetHierarchyParent() == 0) // no parent
			{
				bool inserted = false;
				for (int i = 0; i < hierarchyList.size(); ++i)
				{
					NameTag* entityInList = ecs.getComponent<NameTag>(hierarchyList[i]);

					if (entityInList->GetHierarchyIndex() > nameTagComponent->GetHierarchyIndex()) // Found the slot to insert current entity
					{
						hierarchyList.emplace(hierarchyList.begin() + i, entity);
						inserted = true;

						break;
					}
				}
				if (!inserted)
				{
					hierarchyList.emplace_back(entity);
				}
			}
		}

		filter.Clear();
	}

	void Hierarchy::reorderingHierarchy(EntityID payloadEntity, EntityID acceptEntity, bool acceptEntityTreeNode)
	{
		NameTag* payloadNameTagComponent = ecs.getComponent<NameTag>(payloadEntity);
		EntityID payloadParent = payloadNameTagComponent->GetHierarchyParent();
		EntityID payloadIndexInParent = payloadNameTagComponent->GetHierarchyIndex();
		std::vector<EntityID> payloadChildren = payloadNameTagComponent->GetHierarchyChildren();

		NameTag* acceptNameTagComponent;
		EntityID acceptParent = 0;
		EntityID acceptIndexInParent = 0;
		std::vector<EntityID> acceptChildren;

		if (acceptEntity != 0)
		{
			acceptNameTagComponent = ecs.getComponent<NameTag>(acceptEntity);
			acceptParent = acceptNameTagComponent->GetHierarchyParent();
			acceptIndexInParent = acceptNameTagComponent->GetHierarchyIndex(); 
			acceptChildren = acceptNameTagComponent->GetHierarchyChildren();
		}

		//auto& currEntityIDHierarchyInfo = hierarchyMap[acceptEntity];
		//auto& payloadEntityIDHierarchyInfo = hierarchyMap[payloadEntity];

		if (searchForChild(payloadEntity, acceptEntity)) // Making sure parent / grandparent cannot be moved to the child
		{
			return;
		}

		if (acceptEntity != payloadEntity &&
			!(acceptParent == payloadParent
				&& (acceptIndexInParent + 1) == payloadIndexInParent) || acceptEntityTreeNode)
		{
			if (payloadEntity == acceptParent &&
				payloadChildren.size() - 1 == acceptIndexInParent) // check if the payload is the last child of the parent
			{
				return;
			}

			int payloadSiblingsSize = 0;

			if (payloadParent == 0)
			{
				hierarchyList.erase(hierarchyList.begin() + payloadIndexInParent);
				payloadSiblingsSize = hierarchyList.size();
			}
			else
			{
				auto& payloadSiblings = ecs.getComponent<NameTag>(payloadParent)->GetHierarchyChildren();
				payloadSiblings.erase(payloadSiblings.begin() + payloadIndexInParent);
				payloadSiblingsSize = payloadSiblings.size();
			}

			if (acceptEntityTreeNode && acceptEntity != 0) // true means currEntity is a parent and the tree node is open, make it the first child
			{
				ecs.getComponent<NameTag>(payloadEntity)->SetHierarchyParent(acceptEntity);
				acceptChildren.emplace(acceptChildren.begin(), payloadEntity);

				for (int index = 0; index < acceptChildren.size(); ++index)
				{
					ecs.getComponent<NameTag>(acceptChildren[index])->SetHierarchyIndex(index);
				}
			}
			// Just shifting around without changing parent
			else if (payloadParent == acceptParent)
			{
				if (payloadIndexInParent < acceptIndexInParent || (payloadParent == 0 && acceptIndexInParent == 0))
				{
					if (payloadParent == 0)
					{
						hierarchyList.emplace(hierarchyList.begin() + acceptIndexInParent, payloadEntity);
					}
					else
					{
						auto& payloadSiblings = ecs.getComponent<NameTag>(payloadParent)->GetHierarchyChildren();
						payloadSiblings.emplace(payloadSiblings.begin() + acceptIndexInParent, payloadEntity);
					}
				}
				else if (acceptIndexInParent + 1 == payloadSiblingsSize)
				{
					if (payloadParent == 0)
					{
						hierarchyList.emplace_back(payloadEntity);
					}
					else
					{
						auto& payloadSiblings = ecs.getComponent<NameTag>(payloadParent)->GetHierarchyChildren();
						payloadSiblings.emplace_back(payloadEntity);
					}
				}
				else
				{
					if (payloadParent == 0)
					{
						hierarchyList.emplace(hierarchyList.begin() + acceptIndexInParent + 1, payloadEntity);
					}
					else
					{
						auto& payloadSiblings = ecs.getComponent<NameTag>(payloadParent)->GetHierarchyChildren();
						payloadSiblings.emplace(payloadSiblings.begin() + acceptIndexInParent + 1, payloadEntity);
					}
				}
			}
			else // Different parent
			{
				if (payloadParent == 0)
				{
					for (int index = 0; index < hierarchyList.size(); ++index)
					{
						ecs.getComponent<NameTag>(hierarchyList[index])->SetHierarchyIndex(index);
					}
				}
				else
				{
					auto& payloadSiblings = ecs.getComponent<NameTag>(payloadParent)->GetHierarchyChildren();
					for (int index = 0; index < payloadSiblings.size(); ++index)
					{
						ecs.getComponent<NameTag>(payloadSiblings[index])->SetHierarchyIndex(index);
					}
				}

				payloadNameTagComponent->SetHierarchyIndex(acceptParent);
				ecs.getComponent<NameTag>(payloadEntity)->SetHierarchyParent(acceptParent);

				if (acceptParent == 0)
				{
					hierarchyList.emplace(hierarchyList.begin() + acceptIndexInParent + 1, payloadEntity);
				}
				else
				{
					auto& acceptSiblings = ecs.getComponent<NameTag>(acceptParent)->GetHierarchyChildren();
					acceptSiblings.emplace(acceptSiblings.begin() + acceptIndexInParent + 1, payloadEntity);
				}
			}

			if (acceptParent == 0)
			{
				for (int index = 0; index < hierarchyList.size(); ++index)
				{
					ecs.getComponent<NameTag>(hierarchyList[index])->SetHierarchyIndex(index);
				}
			}
			else
			{
				auto& acceptSiblings = ecs.getComponent<NameTag>(acceptParent)->GetHierarchyChildren();

				for (int index = 0; index < acceptSiblings.size(); ++index)
				{
					ecs.getComponent<NameTag>(acceptSiblings[index])->SetHierarchyIndex(index);
				}
			}
		}
	}

	void Hierarchy::makingChildHierarchy(EntityID payloadEntity, EntityID acceptEntity)
	{
		NameTag* payloadNameTagComponent = ecs.getComponent<NameTag>(payloadEntity);
		NameTag* acceptNameTagComponent = ecs.getComponent<NameTag>(acceptEntity);

		EntityID payloadParent = payloadNameTagComponent->GetHierarchyParent();
		EntityID acceptParent = acceptNameTagComponent->GetHierarchyParent();

		EntityID payloadIndexInParent = payloadNameTagComponent->GetHierarchyIndex();
		EntityID acceptIndexInParent = acceptNameTagComponent->GetHierarchyIndex();

		auto& payloadChildren = payloadNameTagComponent->GetHierarchyChildren();
		auto& acceptChildren = acceptNameTagComponent->GetHierarchyChildren();

		//auto& currEntityIDHierarchyInfo = hierarchyMap[acceptEntity];
		//auto& payloadEntityIDHierarchyInfo = hierarchyMap[payloadEntity];

		if (acceptParent != payloadEntity)
		{
			if (searchForChild(payloadEntity, acceptEntity)) // Making sure parent / grandparent cannot be moved to the child
			{
				return;
			}

			if (payloadParent == 0)
			{
				hierarchyList.erase(hierarchyList.begin() + payloadIndexInParent);

				for (int index = 0; index < hierarchyList.size(); ++index)
				{
					ecs.getComponent<NameTag>(hierarchyList[index])->SetHierarchyIndex(index);
				}
			}
			else
			{
				auto& payloadSiblings = ecs.getComponent<NameTag>(payloadParent)->GetHierarchyChildren();
				payloadSiblings.erase(payloadSiblings.begin() + payloadIndexInParent);

				for (int index = 0; index < payloadSiblings.size(); ++index)
				{
					ecs.getComponent<NameTag>(payloadSiblings[index])->SetHierarchyIndex(index);
				}
			}

			payloadNameTagComponent->SetHierarchyParent(acceptEntity);
			acceptChildren.emplace_back(payloadEntity);

			for (int index = 0; index < acceptChildren.size(); ++index)
			{
				ecs.getComponent<NameTag>(acceptChildren[index])->SetHierarchyIndex(index);
			}
		}
	}

	bool Hierarchy::searchForChild(EntityID parentEntity, EntityID entityToFind)
	{
		//for (auto childEntity : hierarchyMap[parentEntity].children)
		for (auto childEntity : ecs.getComponent<NameTag>(parentEntity)->GetHierarchyChildren())
		{
			if (childEntity == entityToFind)
			{
				return true;
			}
			if (ecs.getComponent<NameTag>(childEntity)->GetHierarchyChildren().size())
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
		bool opened = false;

		// Get Name Tag component
		NameTag* nameTagComponent = ecs.getComponent<NameTag>(entityID);

		// Checking if entity has children
		if (!ecs.getComponent<NameTag>(entityID)->GetHierarchyChildren().size()) // No children
		{
			ImGui::Indent();

			// Entity will be a selectable as there are no children
			bool currentItemHovered = false;
			opened = ImGui::Selectable(nameTagComponent->GetName().c_str(), selectedEntity == entityID, ImGuiSelectableFlags_SpanAllColumns);

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
			if (opened)
			{
				selectedEntity = entityID;
			}

			if (ImGui::BeginPopupContextItem())
			{
				selectedEntity = entityID;
				popupOpened = true;
				if (ImGui::Selectable("Remove Entity"))
				{
					EntityID parent = ecs.getComponent<NameTag>(selectedEntity)->GetHierarchyParent();

					if (parent == 0)
					{
						hierarchyList.erase(std::find(hierarchyList.begin(), hierarchyList.end(), selectedEntity));
					}
					else
					{
						auto& siblings = ecs.getComponent<NameTag>(parent)->GetHierarchyChildren();
						siblings.erase(std::find(siblings.begin(), siblings.end(), selectedEntity));
					}

					// Removing all instance of the removed entity
					auto allEntities = ecs.getEntities();
					static auto& sceneManagerInstance = SceneManager::GetInstance();

					for (auto scriptName : sceneManagerInstance->getAllScripts())
					{
						// For each entity
						for (auto currentEntity : allEntities)
						{
							if (!sceneManagerInstance->hasScript(currentEntity, scriptName))
							{
								continue;
							}

							std::vector<ScriptValues> allValues = sceneManagerInstance->getScriptVariables(currentEntity, scriptName);

							for (ScriptValues scriptValue : allValues)
							{
								if (scriptValue.referenceEntityID == selectedEntity) // there is a entity reference 
								{
									if (scriptValue.type == "ScriptAPI.GameObject")
									{
										sceneManagerInstance->setGameObject(currentEntity, scriptName, scriptValue.name, 0);
									}
									else
									{
										sceneManagerInstance->setScriptReference(currentEntity, scriptName, scriptValue.name, 0, scriptValue.type);
									}
								}
							}
						}
					}

					ecs.removeEntity(selectedEntity);

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
		opened = ImGui::TreeNodeEx(nameTagComponent->GetName().c_str(), nodeFlags);

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
				EntityID parent = ecs.getComponent<NameTag>(selectedEntity)->GetHierarchyParent();
				if (parent == 0)
				{
					hierarchyList.erase(std::find(hierarchyList.begin(), hierarchyList.end(), selectedEntity));
				}
				else
				{
					auto& siblings = ecs.getComponent<NameTag>(parent)->GetHierarchyChildren();
					siblings.erase(std::find(siblings.begin(), siblings.end(), selectedEntity));
				}

				// Removing all instance of the removed entity
				auto allEntities = ecs.getEntities();
				static auto& sceneManagerInstance = SceneManager::GetInstance();

				for (auto scriptName : sceneManagerInstance->getAllScripts())
				{
					// For each entity
					for (auto currentEntity : allEntities)
					{
						if (!sceneManagerInstance->hasScript(currentEntity, scriptName))
						{
							continue;
						}

						std::vector<ScriptValues> allValues = sceneManagerInstance->getScriptVariables(currentEntity, scriptName);

						for (ScriptValues scriptValue : allValues)
						{
							if (scriptValue.referenceEntityID == selectedEntity) // there is a entity reference 
							{
								if (scriptValue.type == "ScriptAPI.GameObject")
								{
									sceneManagerInstance->setGameObject(currentEntity, scriptName, scriptValue.name, 0);
								}
								else
								{
									sceneManagerInstance->setScriptReference(currentEntity, scriptName, scriptValue.name, 0, scriptValue.type);
								}
							}
						}
					}
				}

				ecs.removeEntity(selectedEntity);
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
				reorderingHierarchy(payloadEntityID, entityID, opened);
			}
			ImGui::EndDragDropTarget();
		}

		if (opened)
		{
			auto& children = ecs.getComponent<NameTag>(entityID)->GetHierarchyChildren();
			
			std::uint32_t originalSize = children.size();
			for (auto childEntity : children)
			{
				drawHierarchy(childEntity);

				if (originalSize != children.size())
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
		if (currentFilename != SceneManager::GetInstance()->getCurrentScene()) 
		{
			selectedEntity = 0;
			init();
			currentFilename = SceneManager::GetInstance()->getCurrentScene();
		}
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

					auto nameTagComponent = GetNameTag(newEntityID);
					nameTagComponent->SetHierarchyParent(0);
					nameTagComponent->SetHierarchyIndex(hierarchyList.size());

					auto transformComponent = GetTransform(newEntityID);
					transformComponent->SetScale(Vec3(1.f, 1.f, 1.f));

					hierarchyList.emplace_back(newEntityID);

					TDS_INFO("New Entity Created");
				}
				if (ImGui::MenuItem("Square"))
				{
					// Add Sprite or smth to render a square
					Entity newEntity;
					EntityID newEntityID = newEntity.getID();
					newEntity.add<NameTag>();
					newEntity.add<Transform>();
					newEntity.add<UISprite>();
					selectedEntity = newEntityID;

					auto nameTagComponent = ecs.getComponent<NameTag>(newEntityID);
					nameTagComponent->SetHierarchyParent(0);
					nameTagComponent->SetHierarchyIndex(hierarchyList.size());
					hierarchyList.emplace_back(newEntityID);

					auto transformComponent = GetTransform(newEntityID);
					transformComponent->SetScale(Vec3(1.f, 1.f, 1.f));

					TDS_INFO("New Entity Created");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		static auto& sceneManagerInstance = SceneManager::GetInstance();

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
			if (ImGui::TreeNodeEx(sceneManagerInstance->getCurrentScene().c_str(), nodeFlags))
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

				std::uint32_t originalSize = hierarchyList.size();
				for (auto childEntity : hierarchyList)
				{
					drawHierarchy(childEntity);

					if (originalSize != hierarchyList.size())
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
							EntityID parent = ecs.getComponent<NameTag>(selectedEntity)->GetHierarchyParent();

							if (parent == 0)
							{
								hierarchyList.erase(std::find(hierarchyList.begin(), hierarchyList.end(), selectedEntity));
							}
							else
							{
								auto& siblings = ecs.getComponent<NameTag>(parent)->GetHierarchyChildren();
								siblings.erase(std::find(siblings.begin(), siblings.end(), selectedEntity));
							}

							// Removing all instance of the removed entity
							auto allEntities = ecs.getEntities();
							for (auto scriptName : sceneManagerInstance->getAllScripts())
							{
								// For each entity
								for (auto currentEntity : allEntities)
								{
									if (!sceneManagerInstance->hasScript(currentEntity, scriptName))
									{
										continue;
									}

									std::vector<ScriptValues> allValues = sceneManagerInstance->getScriptVariables(currentEntity, scriptName);

									for (ScriptValues scriptValue : allValues)
									{
										if (scriptValue.referenceEntityID == selectedEntity) // there is a entity reference 
										{
											if (scriptValue.type == "ScriptAPI.GameObject")
											{
												sceneManagerInstance->setGameObject(currentEntity, scriptName, scriptValue.name, 0);
											}
											else
											{
												sceneManagerInstance->setScriptReference(currentEntity, scriptName, scriptValue.name, 0, scriptValue.type);
											}
										}
									}
								}
							}

							ecs.removeEntity(selectedEntity);
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