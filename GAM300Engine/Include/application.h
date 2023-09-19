#ifndef APPLICATION
#define APPLICATION

#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "windowswindow.h"
#include "vulkanTools/vulkanInstance.h"
#include "dotnet/ImportExport.h"
#include "dotnet/include/coreclrhost.h" 
#include "ecs/ecs.h"

namespace TDS
{
	class /*DLL_API*/ Application
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

		static void HelloWorld();

		void handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    

		bool initImgui();
	private:
		// Function Pointers to CoreCLR functions
		coreclr_initialize_ptr      initializeCoreClr = nullptr;
		coreclr_create_delegate_ptr createManagedDelegate = nullptr;
		coreclr_shutdown_ptr        shutdownCoreClr = nullptr;

		// Helper Functions
		template<typename FunctType>
		FunctType getCoreClrFuncPtr(const std::string& functionName)
		{
			auto fPtr = reinterpret_cast<FunctType>(GetProcAddress(coreClr, functionName.c_str()));
			if (!fPtr)
				throw std::runtime_error("Unable to get pointer to function.");
			return fPtr;
		}

		// Helper Functions
		template<typename FunctionType>
		FunctionType GetFunctionPtr(const std::string_view& assemblyName, const std::string_view& typeName, const std::string_view& functionName)
		{
			FunctionType managedDelegate = nullptr;
			int result = createManagedDelegate
			(
				hostHandle,
				domainId,
				assemblyName.data(),
				typeName.data(),
				functionName.data(),
				reinterpret_cast<void**>(&managedDelegate)
			);
			// Check if it failed
			if (result < 0)
			{
				std::ostringstream oss;
				oss << std::hex << std::setfill('0') << std::setw(8)
					<< "[DotNetRuntime] Failed to get pointer to function \""
					<< typeName << "." << functionName << "\" in assembly (" << assemblyName << "). "
					<< "Error 0x" << result << "\n";
				throw std::runtime_error(oss.str());
			}
			return managedDelegate;
		}

		std::string buildTpaList(const std::string& directory);

	private:
		void startScriptEngine();
		void stopScriptEngine();
		// References to CoreCLR key components
		HMODULE coreClr = nullptr;
		void* hostHandle = nullptr;
		unsigned int domainId = 0;

	private:
		Application(const Application&);
		//Application& operator=(const Application&) {}

	private:
		WindowsWin						 m_window;
		bool							 m_isRunning{ true };
		std::shared_ptr <VulkanInstance> m_pVKInst;
	};//class application





}//namespace TDS


#endif // !APPLICATION

