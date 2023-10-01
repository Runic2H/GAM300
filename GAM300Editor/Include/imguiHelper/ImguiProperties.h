#ifndef IMGUI_PROPERTIES
#define IMGUI_PROPERTIES

#include "ImguiHelper.h"

namespace TDS 
{
	class Properties : public LevelEditorPanel
	{
	public:
		Properties();

		void update();

		void ImguiComponentDisplay(std::string componentName, IComponent* componentBase);

	private:
	};
}

#endif // IMGUI_PROPERTIES
