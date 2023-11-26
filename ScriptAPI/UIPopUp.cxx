#include "UIPopUp.hxx"
#include "AI/UIPopupManager.h"
#include "TypeConversion.hxx"
namespace ScriptAPI
{
	void UIPopUpManager::TogglePopUp(int entityID, bool toggleCondition)
	{
		TDS::UIPopUpManager::TogglePopUp(entityID, toggleCondition);
	}


	//Call this on awake only!! Please dont keep calling this function in Update() cause its expensive to keep recursively searching for the children.
	unsigned int UIPopUpManager::getChildPopUp(unsigned int EntityID , System::String^ childName)
	{
		return TDS::UIPopUpManager::getChildPopUp(EntityID, toStdString(childName));
	}
	
}