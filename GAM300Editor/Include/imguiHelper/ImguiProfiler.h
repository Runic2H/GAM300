#ifndef IMGUI_PROFILER
#define IMGUI_PROFILER

#include "ImguiHelper.h"

namespace TDS 
{
	class Profiler : public LevelEditorPanel
	{
	public:
		Profiler();

		void getVulkanInfo();
		void update();
		std::string GPU_name = "GPU: ";
		std::string Vulkan_API_version = "API Version: ";

	private:
		std::vector<float> fps_log;
		std::vector<float> ms_log;

		std::vector<std::string> caps_log;

	};
}

#endif // IMGUI_CONSOLE
