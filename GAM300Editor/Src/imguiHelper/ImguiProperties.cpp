#include "imguiHelper/ImguiProperties.h"
#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
	Properties::Properties()
	{
		flags = ImGuiWindowFlags_NoCollapse;
		panelTitle = "Properties";
		windowPadding = ImVec2(0.f, 0.f);
	}

	void Properties::update()
	{
		std::shared_ptr<Hierarchy> hierarchyPanel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[PanelTypes::HIERARCHY]);

		// If there is a selected entity
		if (EntityID selectedEntity = hierarchyPanel->getSelectedEntity())
		{
			std::vector<std::string> allComponentNames = ecs.getAllRegisteredComponents();

			ImGuiTreeNodeFlags nodeFlags =
				ImGuiTreeNodeFlags_DefaultOpen |
				ImGuiTreeNodeFlags_FramePadding |
				ImGuiTreeNodeFlags_SpanAvailWidth |
				ImGuiTreeNodeFlags_SpanFullWidth |
				ImGuiTreeNodeFlags_Selected;

			for (auto componentName : allComponentNames)
			{
				IComponent* componentBase = getComponentByName(componentName, selectedEntity);

				if (componentName == "Name Tag" && ImGui::BeginTable("###", 2))
				{
					//componentBase->ImGuiDisplay();
					ImGui::EndTable();
					continue;
				}

				if (!componentBase)
				{
					continue;
				}

				bool componentOpen = ImGui::TreeNodeEx(componentName.c_str(), nodeFlags);

				if (ImGui::BeginPopupContextItem("componentEditPopup"))
				{
					if (ImGui::Selectable("Remove Component"))
					{
						removeComponentByName(componentName, selectedEntity);
					}

					ImGui::EndPopup();
				}

				if (rightClick && ImGui::IsItemHovered())
				{
					ImGui::OpenPopup("componentEditPopup");
				}

				if (componentOpen)
				{
					if (ImGui::BeginTable("###", 2, /*ImGuiTableFlags_Borders |*/ ImGuiTableFlags_NoPadInnerX, ImVec2(0.0f, 5.5f)))
					{
						ImGui::TableNextRow();

						ImGui::TableNextColumn();
						ImGui::TableNextColumn();
						ImGui::PushItemWidth(-FLT_MIN); // Right-aligned

						//componentBase->ImGuiDisplay();

						ImGui::PopItemWidth();
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}
			}

			if (ImGui::BeginPopupContextItem("componentAddPopup"))
			{
				for (auto componentName : allComponentNames)
				{
					if (!getComponentByName(componentName, selectedEntity) && ImGui::Selectable(componentName.c_str()))
					{
						addComponentByName(componentName, selectedEntity);
					}
				}
				ImGui::EndPopup();
			}

			// Add component button
			ImGuiStyle& style = ImGui::GetStyle();

			float size = ImGui::CalcTextSize("Add Component").x + style.FramePadding.x * 2.0f;
			float avail = ImGui::GetContentRegionAvail().x;

			float off = (avail - size) * 0.5f;
			if (off > 0.0f)
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

			if (ImGui::Button("Add Component", ImVec2(100.f, 20.f)))
			{
				ImGui::OpenPopup("componentAddPopup");
			}
		}
	}
}