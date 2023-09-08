
#include "application.h"

namespace TDS
{
     Application::Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname)
        :m_window(hinstance, nCmdShow, classname)
     {
         m_window.createWindow();
         m_pVKInst = std::make_shared<VulkanInstance>(m_window);
	 }

     void Application::Initialize()
     {
         
     }
     void Application::Update()
     {
         while (m_isRunning)
         {
             m_isRunning = m_window.processInputEvent();
             m_pVKInst.get()->drawFrame();
         }
         vkDeviceWaitIdle(m_pVKInst.get()->getVkLogicalDevice());
     }
     Application::~Application()
     {
         m_window.~WindowsWin();
        
     }

}// end TDS