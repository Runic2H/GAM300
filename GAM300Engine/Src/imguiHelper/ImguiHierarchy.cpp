#include "imguiHelper/ImguiHierarchy.h"

namespace TDS
{
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

	void Hierarchy::update()
	{
		for (auto entityID : ECS::getEntities())
		{
			if (NameTag* nameTagComponent = ECS::getComponent<NameTag>(entityID))
			{
				if (ImGui::Selectable(nameTagComponent->GetNameTag().c_str(), selectedEntity == entityID))
				{
					selectedEntity = entityID;
				}
			}
		}
	}
}