/*!*************************************************************************
****
\file Logger.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD3400
\par Section: a
\par assignment: M1
\date 01-10-2023
\brief  This file implements a logging system using spdlog, macros such as
		TDS_INFO() are TDS_WARN() used to call logging system info of their
		respective spdlog::level.
****************************************************************************
***/
#ifndef TDS_LOGGER
#define TDS_LOGGER

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include <string>
#include <memory>
#include "dotnet/ImportExport.h"
#define TDS_API __declspec(dllexport)
namespace TDS
{
	//template class TDS_API std::shared_ptr<spdlog::logger>;
	class DLL_API Log
	{
	public:
		static void Init();


		/*!*************************************************************************
		Retrieves CoreLogger info
		****************************************************************************/
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/*!*************************************************************************
		Retrieves ClientLogger info
		****************************************************************************/
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		/*!*************************************************************************
		Outputs spdlog info via output string stream for ImGui
		****************************************************************************/
		static std::string GetImguiLog();
		

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::ostringstream oss;
	};
} //end of namespace TDS

//Macros for logger
//Trace is to track variable changes during execution like Window Size etc
#define TDS_TRACE(...)	 ::TDS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TDS_INFO(...)	 ::TDS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TDS_WARN(...)	 ::TDS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TDS_ERROR(...)	 ::TDS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TDS_CRITICAL(...) ::TDS::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Assertion failed, it will track where it happened and print it in console (for debug)
#define TDS_EXO_ASSERT(x, ...) {if((x)) { TDS_EXO_CRITICAL("Assert Failed: {} {}\n\tIn File:{}\n\tLine: {}",x, __VA_ARGS__,__FILE__,__LINE__);__debugbreak();}}

//Client 
//#define TDS_TRACE(...) ::TDS::Log::GetClientLogger()->trace(__VA_ARGS__)
//#define TDS_INFO(...)  ::TDS::Log::GetClientLogger()->info(__VA_ARGS__)
//#define TDS_WARN(...)  ::TDS::Log::GetClientLogger()->warn(__VA_ARGS__)
//#define TDS_ERROR(...) ::TDS::Log::GetClientLogger()->error(__VA_ARGS__)
//#define TDS_CRITICAL(...) ::TDS::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif