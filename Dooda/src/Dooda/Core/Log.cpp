#include "Ddpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Dooda
{

	Ref<spdlog::logger> Log::sd_CoreLogger;
	Ref<spdlog::logger> Log::sd_ClientLogger;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Dooda.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		sd_CoreLogger = std::make_shared<spdlog::logger>("Dooda", begin(logSinks), end(logSinks));
		spdlog::register_logger(sd_CoreLogger);

		sd_CoreLogger->set_level(spdlog::level::trace); 
		sd_CoreLogger->flush_on(spdlog::level::trace);

		sd_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(sd_ClientLogger);

		sd_ClientLogger->set_level(spdlog::level::trace);
		sd_ClientLogger->flush_on(spdlog::level::trace);
	}

}
