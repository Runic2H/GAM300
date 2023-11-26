#include "UIPopUp.hxx"
#include "AI/UIPopupManager.h"

namespace ScriptAPI
{
	void UIPopUp::ToggleViewFrom2D(int entityID, bool toggleCondition)
	{
		TDS::UIPopUpManager::TogglePopUp(entityID, toggleCondition);
	}
}