#ifndef APPLICATION
#define APPLICATION

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <chrono>

#include "windowswindow.h"
#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/Descriptor.h"
#include "vulkanTools/Renderer.h"
#include "vulkanTools/Buffer.h"
#include "vulkanTools/RendererManager.h"
#include "camera/camera.h"
#include "AssetManagement/AssetManager.h"
#include "vulkanTools/PointLightSystem.h"
#include "imguiHelper/ImguiHelper.h"
namespace TDS
{
	class Application
	{
	public:

		Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname, WNDPROC wndproc);
		~Application();

		static constexpr int ENTITY_COUNT = 5;
		static constexpr int MIN_ENTITY_ID = 0;
		static constexpr int MAX_ENTITY_ID = ENTITY_COUNT - 1;

		void   Initialize();
		void   Update();
		void   Render() {}
		void   Exit() {}
		void   Run();

		//static void HelloWorld();

		void handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	private:
		bool initImgui();
		Application(const Application&);


	private:
		WindowsWin						 m_window;
		bool							 m_isRunning{ true };
		AssetManager					 m_AssetManager;

		std::chrono::time_point<std::chrono::high_resolution_clock>Clock{};
		std::shared_ptr <VulkanInstance> m_pVKInst;
		std::unique_ptr<DescriptorPool>  m_globalPool{};
		//std::unique_ptr<DescriptorPool>  m_guipool{};
		std::shared_ptr<Renderer>		 m_Renderer/*{ m_window, * m_pVKInst.get() }*/;
		TDSCamera m_camera{ -90.0f ,0.f };
		std::shared_ptr<Model> models;
		//VkSampler sampling;
		struct UniformBufferObject
		{
			Mat4 model;
			Mat4 view;
			Mat4 proj;
		};

	};//class application



}//namespace TDS


#endif // !APPLICATION

