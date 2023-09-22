#ifndef IMGUI_HIERARCHY
#define IMGUI_HIERARCHY

#include "ImguiHelper.h"

namespace TDS 
{
	class Hierarchy : public LevelEditorPanel
	{
	public:
		Hierarchy();

		void update();

		EntityID getSelectedEntity() { return selectedEntity; }
		void setSelectedEntity(EntityID _selectedEntity) { selectedEntity = _selectedEntity; }

	private:
		EntityID selectedEntity;
	};
}

#endif // IMGUI_HIERARCHY
