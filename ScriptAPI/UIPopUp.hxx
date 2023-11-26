#pragma once
namespace ScriptAPI
{

	public ref class UIPopUp
	{
	public:
		static void ToggleViewFrom2D(int entityID, bool toggleCondition);
		static bool CollidedWithUI(int entityID, bool toggleCondition);
	};
}