// Application.cpp
#include <shlwapi.h>                // GetModuleFileNameA(), PathRemoveFileSpecA()
#pragma comment(lib, "shlwapi.lib") // Needed for <shlwapi.h>
#include <vector>
#include <array>
#include <sstream>
#include <filesystem>
#include "application.h"
#include "sceneManager/sceneManager.h"

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
         auto& sceneManager = SceneManager::GetInstance();
         sceneManager->Init();
     }

     void Application::Run()
     {
         startScriptEngine();

         // Step 1: Get Functions
         auto init = GetFunctionPtr<void(*)(void)>
             (
                 "ScriptAPI",
                 "ScriptAPI.EngineInterface",
                 "Init"
             );
         auto addScript = GetFunctionPtr<bool(*)(int, const char*)>
             (
                 "ScriptAPI",
                 "ScriptAPI.EngineInterface",
                 "AddScriptViaName"
             );
         auto executeUpdate = GetFunctionPtr<void(*)(void)>
             (
                 "ScriptAPI",
                 "ScriptAPI.EngineInterface",
                 "ExecuteUpdate"
             );

         // Step 2: Initialize
         init();// Step 1: Get Functions

         //addScript(0, "Test");

         // Load
         while (true)
         {
             if (GetKeyState(VK_ESCAPE) & 0x8000)
                 break;

             // Step 4: Run the Update loop for our scripts
             executeUpdate();
         }

         stopScriptEngine();
     }

     void Application::Update()
     {
         while (m_isRunning)
         {
             Run();
             m_isRunning = m_window.processInputEvent();
             m_pVKInst.get()->drawFrame();
         }
         vkDeviceWaitIdle(m_pVKInst.get()->getVkLogicalDevice());
     }
     Application::~Application()
     {
         m_window.~WindowsWin();
     }

     void Application::HelloWorld()
     {
         std::cout << "Hello Native World!" << std::endl;
     }

     void Application::startScriptEngine()
     {
         // Step 1: Loading the coreclr.dll
         // Get the current executable directory so that we can find the coreclr.dll to load
         std::string runtimePath(MAX_PATH, '\0');
         GetModuleFileNameA(nullptr, runtimePath.data(), MAX_PATH);
         PathRemoveFileSpecA(runtimePath.data());
         // Since PathRemoveFileSpecA() removes from data(), the size is not updated, so we must manually update it
         runtimePath.resize(std::strlen(runtimePath.data()));

         std::filesystem::current_path(runtimePath);

         // Construct the CoreCLR path
         std::string coreClrPath(runtimePath); // Works
         coreClrPath += "\\coreclr.dll";
         
         // Load the CoreCLR DLL
         coreClr = LoadLibraryExA(coreClrPath.c_str(), nullptr, 0);
         if (!coreClr)
             throw std::runtime_error("Failed to load CoreCLR.");

         // Step 2: Get CoreCLR hosting functions
         initializeCoreClr = getCoreClrFuncPtr<coreclr_initialize_ptr>("coreclr_initialize");
         createManagedDelegate = getCoreClrFuncPtr<coreclr_create_delegate_ptr>("coreclr_create_delegate");
         shutdownCoreClr = getCoreClrFuncPtr<coreclr_shutdown_ptr>("coreclr_shutdown");

         // Step 3: Construct AppDomain properties used when starting the runtime
         std::string tpaList = buildTpaList(runtimePath);
         // Define CoreCLR properties
         std::array propertyKeys =
         {
             "TRUSTED_PLATFORM_ASSEMBLIES",      // Trusted assemblies (like the GAC)
             "APP_PATHS",                        // Directories to probe for application assemblies
         };
         std::array propertyValues =
         {
             tpaList.c_str(),
             runtimePath.c_str()
         };

         // Step 4: Start the CoreCLR runtime
         int result = initializeCoreClr
         (
             runtimePath.c_str(),     // AppDomain base path
             "SampleHost",            // AppDomain friendly name, this can be anything you want really
             propertyKeys.size(),     // Property count
             propertyKeys.data(),     // Property names
             propertyValues.data(),   // Property values
             &hostHandle,             // Host handle
             &domainId                // AppDomain ID
         );
         // Check if intiialization of CoreCLR failed
         if (result < 0)
         {
             std::ostringstream oss;
             oss << std::hex << std::setfill('0') << std::setw(8)
                 << "Failed to initialize CoreCLR. Error 0x" << result << "\n";
             throw std::runtime_error(oss.str());
         }
     }

     std::string Application::buildTpaList(const std::string& directory)
     {
         // Constants
         static const std::string SEARCH_PATH = directory + "\\*.dll";
         static constexpr char PATH_DELIMITER = ';';
         // Create a osstream object to compile the string
         std::ostringstream tpaList;
         // Search the current directory for the TPAs (.DLLs)
         WIN32_FIND_DATAA findData;
         HANDLE fileHandle = FindFirstFileA(SEARCH_PATH.c_str(), &findData);
         if (fileHandle != INVALID_HANDLE_VALUE)
         {
             do
             {
                 // Append the assembly to the list
                 tpaList << directory << '\\' << findData.cFileName << PATH_DELIMITER;
             } while (FindNextFileA(fileHandle, &findData));
             FindClose(fileHandle);
         }
         return tpaList.str();
     }

     void Application::stopScriptEngine()
     {
         // Shutdown CoreCLR
         const int RESULT = shutdownCoreClr(hostHandle, domainId);
         if (RESULT < 0)
         {
             std::stringstream oss;
             oss << std::hex << std::setfill('0') << std::setw(8)
                 << "Failed to shut down CoreCLR. Error 0x" << RESULT << "\n";
             throw std::runtime_error(oss.str());
         }
     }

}// end TDS