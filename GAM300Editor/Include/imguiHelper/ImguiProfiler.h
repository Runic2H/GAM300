#ifndef IMGUI_PROFILER
#define IMGUI_PROFILER

#include "ImguiHelper.h"

namespace TDS 
{
	class Profiler : public LevelEditorPanel
	{
	public:
		Profiler();

		static void getVulkanInfo(ImGui_ImplVulkan_InitInfo& vulkanInfo);
		void update();
		std::string GPU_name = "GPU: ";
		std::string Vulkan_API_version = "API Version: ";

	private:
		static ImGui_ImplVulkan_InitInfo m_vulkanInfo;
		VkPhysicalDeviceProperties deviceProperties;
		std::vector<float> fps_log;
		std::vector<float> ms_log;

		std::vector<std::string> caps_log;

	};
}

#endif // IMGUI_CONSOLE
