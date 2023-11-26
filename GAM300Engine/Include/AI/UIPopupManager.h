#pragma once
#include "dotnet/ImportExport.h"
#include "ecs/ecs.h"
namespace TDS
{
	class DLL_API UIPopUpManager
	{
		public:
			static void TogglePopUp(EntityID popUpMain, bool condition);
			static EntityID getChildPopUp(EntityID popUpMain, std::string_view name);
	};
}