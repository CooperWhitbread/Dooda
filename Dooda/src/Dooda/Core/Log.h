#pragma once
#include "Dooda/Core/Core.h"

#pragma warning(push, 0) // This ignores all warnings raised inside External headers
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Dooda
{

	class Log
	{
	public:
		static void Init();

	public: //Getters
		inline static Ref<spdlog::logger>& GetCoreLogger() { return sd_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return sd_ClientLogger; }

	private: //Variables
		static Ref<spdlog::logger> sd_CoreLogger;
		static Ref<spdlog::logger> sd_ClientLogger;
	};
}

//Core engine log macros
#define DD_CORE_TRACE(...)		::Dooda::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DD_CORE_INFO(...)		::Dooda::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DD_CORE_WARN(...)		::Dooda::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DD_CORE_ERROR(...)		::Dooda::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DD_CORE_CRITICAL(...)	::Dooda::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define DD_TRACE(...)			::Dooda::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DD_INFO(...)			::Dooda::Log::GetClientLogger()->info(__VA_ARGS__)
#define DD_WARN(...)			::Dooda::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DD_ERROR(...)			::Dooda::Log::GetClientLogger()->error(__VA_ARGS__)
#define DD_CRITICAL(...)		::Dooda::Log::GetClientLogger()->critical(__VA_ARGS__) 
