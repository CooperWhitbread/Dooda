#include "Ddpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Dooda
{

	Ref<spdlog::logger> Log::d_CoreLogger;
	Ref<spdlog::logger> Log::d_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		d_CoreLogger = spdlog::stdout_color_mt("Dooda");
		d_CoreLogger->set_level(spdlog::level::trace); 
		d_ClientLogger = spdlog::stdout_color_mt("App");
		d_ClientLogger->set_level(spdlog::level::trace);
	}

}
