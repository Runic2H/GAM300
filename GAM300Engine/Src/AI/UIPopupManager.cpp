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
    EntityID UIPopUpManager::getChildPopUp(EntityID popUpMain, std::string_view name)
    {
        NameTag* MainPopup = ecs.getComponent<NameTag>(popUpMain);
        MainPopup->GetName();

        if (MainPopup == nullptr)
            return 0;
      
        std::function<EntityID(EntityID)> findChildByName;
        findChildByName = [&](EntityID current) -> EntityID
        {
            auto currentTag = ecs.getComponent<NameTag>(current);
            if (currentTag == nullptr)
                return 0;


            if (currentTag->GetName() == name)
                return current;


            for (auto& childID : currentTag->GetHierarchyChildren())
            {
                EntityID found = findChildByName(childID);
                if (found != 0)
                    return found;
            }

            return 0; 
        };

        return findChildByName(popUpMain);
        
    }
}