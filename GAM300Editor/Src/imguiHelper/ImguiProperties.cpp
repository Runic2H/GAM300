/*!*************************************************************************
****
\file ImguiProperties.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the Level Editor Properties
		panel
****************************************************************************
***/


#include "imguiHelper/ImGuiFunctionHelper.h"

#include "imguiHelper/ImguiProperties.h"
#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
	/*!*************************************************************************
	This function initializes the Properties panel
	****************************************************************************/
	Properties::Properties()
	{
		flags = ImGuiWindowFlags_NoCollapse;
		panelTitle = "Properties";
		windowPadding = ImVec2(0.f, 0.f);
	}

	/*!*************************************************************************
	This function is the update function for Properties panel
	****************************************************************************/
	void Properties::update()
	{
		std::shared_ptr<Hierarchy> hierarchyPanel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[PanelTypes::HIERARCHY]);
		auto& sceneManagerInstance = SceneManager::GetInstance();

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

			int i = 0;
			for (auto componentName : allComponentNames)
			{
				IComponent* componentBase = getComponentByName(componentName, selectedEntity);

				if (componentName == "Name Tag" && ImGui::BeginTable("###", 2))
				{
					auto nameTagComponent = reinterpret_cast<NameTag*>(componentBase);
					nameTagComponent->SetName(ImguiInput("", nameTagComponent->GetName()));
					//ImguiInput("", static_cast<int>(hierarchyPanel->hierarchyMap[selectedEntity].parent));
					//ImguiInput("", hierarchyPanel->hierarchyMap[selectedEntity].indexInParent);

					ImGui::EndTable();

					continue;
				}

				if (!componentBase)
				{
					continue;
				}

				bool componentOpen = ImGui::TreeNodeEx(componentName.c_str(), nodeFlags);

				ImGui::PushID(i);
				if (ImGui::BeginPopupContextItem("componentEditPopup"))
				{
					if (componentName != "Name Tag" && componentName != "Transform" && ImGui::Selectable("Remove Component"))
					{
						removeComponentByName(componentName, selectedEntity);
						TDS_INFO("Removed Component");
					}

					ImGui::EndPopup();
				}

				if (rightClick && ImGui::IsItemHovered())
				{
					ImGui::OpenPopup("componentEditPopup");
				}
				ImGui::PopID();
				++i;

				if (componentOpen)
				{
					if (ImGui::BeginTable("###", 2, /*ImGuiTableFlags_Borders |*/ ImGuiTableFlags_NoPadInnerX, ImVec2(0.0f, 5.5f)))
					{
						ImGui::TableNextRow();

						ImGui::TableNextColumn();
						ImGui::TableNextColumn();
						ImGui::PushItemWidth(-FLT_MIN); // Right-aligned

						ImguiComponentDisplay(componentName, componentBase);

						ImGui::PopItemWidth();
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}
			}

			for (auto scriptName : sceneManagerInstance->getAllScripts())
			{
				if (!sceneManagerInstance->hasScript(selectedEntity, scriptName))
				{
					continue;
				}

				if (ImGui::TreeNodeEx(scriptName.c_str(), nodeFlags))
				{
					//ImGui::PushID(selectedEntity);
					if (ImGui::BeginTable("###", 2, /*ImGuiTableFlags_Borders |*/ ImGuiTableFlags_NoPadInnerX, ImVec2(0.0f, 5.5f)))
					{
						ImGui::TableNextRow();

						ImGui::TableNextColumn();
						ImGui::TableNextColumn();
						ImGui::PushItemWidth(-FLT_MIN); // Right-aligned

						std::vector<ScriptValues> allValues = sceneManagerInstance->getScriptVariables(selectedEntity, scriptName);

						for (ScriptValues scriptValue : allValues)
						{
							if (scriptValue.type == "System.Boolean")
							{
								bool value = scriptValue.value == "False" ? false : true;
								value = ImguiInput(scriptValue.name, value);
								sceneManagerInstance->setBool(selectedEntity, scriptName, scriptValue.name, value);
							}
							else if (scriptValue.type == "System.Int16"
								|| scriptValue.type == "System.Int32"
								|| scriptValue.type == "System.Int64"
								|| scriptValue.type == "System.UInt16"
								|| scriptValue.type == "System.UInt32"
								|| scriptValue.type == "System.UInt64"
								|| scriptValue.type == "System.Byte"
								|| scriptValue.type == "System.SByte")
							{
								int value = std::stoi(scriptValue.value);
								value = ImguiInput(scriptValue.name, value);
								sceneManagerInstance->setInt(selectedEntity, scriptName, scriptValue.name, value);
							}
							else if (scriptValue.type == "System.Double")
							{
								float value = std::stod(scriptValue.value);
								value = ImguiInput(scriptValue.name, value);
								sceneManagerInstance->setDouble(selectedEntity, scriptName, scriptValue.name, static_cast<double>(value));
							}
							else if (scriptValue.type == "System.Single")
							{
								float value = std::stod(scriptValue.value);
								value = ImguiInput(scriptValue.name, value);
								sceneManagerInstance->setFloat(selectedEntity, scriptName, scriptValue.name, value);
							}
							else // scripts
							{
								// To Do 

							}
						}

						ImGui::PopItemWidth();
						ImGui::EndTable();
					}
					ImGui::TreePop();
				}
			}

			// all script names
			// call manage side to gimme variables that the script has

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

			if (ImGui::GetCursorPosY() < ImGui::GetWindowHeight())
			{
				ImGui::SetNextWindowPos(ImVec2(ImGui::GetContentRegionAvail().x / 2 + ImGui::GetWindowPos().x + style.FramePadding.x * 2.0f, ImGui::GetCursorPosY()), ImGuiCond_Appearing, ImVec2(0.5f, 0.0f));
			}
			else
			{
				ImGui::SetNextWindowPos(ImVec2(ImGui::GetContentRegionAvail().x / 2 + ImGui::GetWindowPos().x + style.FramePadding.x * 2.0f, ImGui::GetWindowHeight()), ImGuiCond_Appearing, ImVec2(0.5f, 0.0f));
			}
			ImGui::SetNextWindowSize(ImVec2(150.f, 0.f));
			
			if (ImGui::BeginPopupContextItem("componentAddPopup"))
			{
				for (auto componentName : allComponentNames)
				{
					if (!getComponentByName(componentName, selectedEntity) && ImGui::Selectable(componentName.c_str()))
					{
						addComponentByName(componentName, selectedEntity);
						TDS_INFO("Added Component");
					}
				}
				for (auto scriptName : sceneManagerInstance->getAllScripts())
				{
					if (!sceneManagerInstance->hasScript(selectedEntity, scriptName) && ImGui::Selectable(scriptName.c_str()))
					{
						sceneManagerInstance->addScript(selectedEntity, scriptName);
					}
				}
				ImGui::EndPopup();
			}
		}
	}

	/*!*************************************************************************
	This function is the helper function for Properties panel
	****************************************************************************/
	void Properties::ImguiComponentDisplay(std::string componentName, IComponent* componentBase)
	{
		rttr::type type = rttr::type::get_by_name(componentName);
		rttr::instance componentInstance = componentBase;

		for (rttr::property propertyName : type.get_properties())
		{
			if (propertyName.get_type() == rttr::type::get<int>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<int>()));
			}
			if (propertyName.get_type() == rttr::type::get<EntityID>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<int>()));
			}
			else if (propertyName.get_type() == rttr::type::get<float>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<float>()));
			}
			else if (propertyName.get_type() == rttr::type::get<bool>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<bool>()));
			}
			else if (propertyName.get_type() == rttr::type::get<std::string>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<std::string>()));
			}
			else if (propertyName.get_type() == rttr::type::get<Vec2>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<Vec2>()));
			}
			else if (propertyName.get_type() == rttr::type::get<Vec3>())
			{
				propertyName.set_value(componentInstance, ImguiInput(propertyName.get_name().to_string(), propertyName.get_value(componentInstance).convert<Vec3>()));
			}
		}
	}

	/*!*************************************************************************
	This function is a helper function for draw TEXT variables
	****************************************************************************/
	std::string ImguiInput(std::string variableName, std::string textVariable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		char temp[100];
		strcpy_s(temp, textVariable.c_str());
		ImGui::InputText(("##" + variableName).c_str(), temp, 100);

		return std::string(temp);
	}

	/*!*************************************************************************
	This function is a helper function for draw BOOl variables
	****************************************************************************/
	bool ImguiInput(std::string variableName, bool boolVariable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		ImGui::Checkbox(("##" + variableName).c_str(), &boolVariable);

		return boolVariable;
	}

	/*!*************************************************************************
	This function is a helper function for draw INT variables
	****************************************************************************/
	int ImguiInput(std::string variableName, int intVariable, float speed, int min, int max)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		ImGui::DragInt(("##" + variableName).c_str(), &intVariable, speed, min, max);

		return intVariable;
	}

	/*!*************************************************************************
	This function is a helper function for draw FLOAT variables
	****************************************************************************/
	float ImguiInput(std::string variableName, float floatVariable, float speed, float min, float max)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		ImGui::DragFloat(("##" + variableName).c_str(), &floatVariable, speed, min, max);

		return floatVariable;
	}

	/*!*************************************************************************
	This function is a helper function for draw VEC2 variables
	****************************************************************************/
	Vec2 ImguiInput(std::string variableName, Vec2 Vec2Variable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		float temp[2]{ Vec2Variable.x, Vec2Variable.y };
		ImGui::DragFloat2(("##" + variableName).c_str(), temp, 0.1f);
		Vec2Variable.x = temp[0];
		Vec2Variable.y = temp[1];

		return Vec2Variable;
	}

	/*!*************************************************************************
	This function is a helper function for draw VEC3 variables
	****************************************************************************/
	Vec3 ImguiInput(std::string variableName, Vec3 Vec3Variable)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(variableName.c_str());

		ImGui::TableNextColumn();
		float temp[3]{ Vec3Variable.x, Vec3Variable.y, Vec3Variable.z };
		ImGui::DragFloat3(("##" + variableName).c_str(), temp, 0.1f);
		Vec3Variable.x = temp[0];
		Vec3Variable.y = temp[1];
		Vec3Variable.z = temp[2];

		return Vec3Variable;
	}
}