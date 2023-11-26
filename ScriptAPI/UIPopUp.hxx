#pragma once
namespace ScriptAPI
{

	public ref class UIPopUpManager
	{
	public:
		static void TogglePopUp(int entityID, bool toggleCondition);
		static unsigned int getChildPopUp(unsigned int EntityID, System::String^ childName);
		
	};
}