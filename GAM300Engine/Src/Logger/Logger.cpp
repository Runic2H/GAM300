#include "Logger/Logger.h"
#include "spdlog/sinks/ostream_sink.h"

namespace TDS
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::ostringstream Log::oss; // stream for imgui logger window

	void Log::Init()
	{
		//set pattern output in console(Date, month, time)
		spdlog::set_pattern("%^[%b:%d %T] %n[%l]: %v%$");

		//Create a multhithreaded console logger 
		s_CoreLogger = spdlog::stdout_color_mt("TDSENGINE"); // Core
		s_CoreLogger->set_level(spdlog::level::trace);
		auto& listOfSink = s_CoreLogger->sinks();
		listOfSink.emplace_back(std::make_shared<spdlog::sinks::ostream_sink_st>(oss));

		s_ClientLogger = spdlog::stdout_color_mt("TDS"); // Client
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	std::string Log::GetImguiLog()
	{
		return oss.str();
	}
} //end of namespace