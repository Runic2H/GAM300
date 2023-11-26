#include "AI/UIPopupManager.h"
#include "components/components.h"
namespace TDS
{
	void UIPopUpManager::TogglePopUp(EntityID popUp, bool condition)
	{
		NameTag* MainPopup = ecs.getComponent<NameTag>(popUp);
		
		if (MainPopup == nullptr)
			return;

		if (MainPopup->GetHierarchyParent() == 0)
		{
            std::function<void(EntityID, bool)> updateDescendantsActiveness = nullptr;
            MainPopup->SetIsActive(condition);
            updateDescendantsActiveness = [&](EntityID parent, bool isActive)
            {
                auto parentTag = ecs.getComponent<NameTag>(parent);
                if (parentTag == nullptr)
                    return;

                for (auto& child : parentTag->GetHierarchyChildren())
                {
                    auto childTag = ecs.getComponent<NameTag>(child);
                    if (childTag != nullptr)
                    {
                        childTag->SetIsActive(condition);
                        updateDescendantsActiveness(child, condition);
                    }
                }
            };	
		}
	}
}