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
			std::vector<std::string> allComponentNames = ECS::getAllRegisteredComponents();

			ImGuiTreeNodeFlags nodeFlags =
				ImGuiTreeNodeFlags_DefaultOpen |
				ImGuiTreeNodeFlags_FramePadding |
				ImGuiTreeNodeFlags_SpanAvailWidth |
				ImGuiTreeNodeFlags_SpanFullWidth |
				ImGuiTreeNodeFlags_Selected;

			for (auto componentName : allComponentNames)
			{
				IComponent* componentBase = getComponentByName(componentName, selectedEntity);

				if (componentName == "NameTag" && ImGui::BeginTable("###", 2))
				{
					componentBase->ImGuiDisplay();
					ImGui::EndTable();
					continue;
				}

				if (componentBase && ImGui::TreeNodeEx(componentName.c_str(), nodeFlags) && ImGui::BeginTable("###", 2, ImGuiTableFlags_Borders, ImVec2(0.0f,  5.5f)))
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::PushItemWidth(0);
					ImGui::TableSetColumnIndex(1);
					ImGui::PushItemWidth(-FLT_MIN); // Right-aligned

					componentBase->ImGuiDisplay();

					ImGui::EndTable();
					ImGui::TreePop();
				}
			}
		}
	}
}