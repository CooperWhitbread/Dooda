#include "ddpch.h"
#include "Instrumentor.h"

namespace Dooda
{
	Instrumentor::Instrumentor()
		: d_CurrentSession(nullptr)
	{
	}

	void Instrumentor::BeginSession(const std::string& name, const std::string& filepath)
	{
		std::lock_guard lock(d_Mutex);
		if (d_CurrentSession) 
		{
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			{ 
				DD_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, d_CurrentSession->Name);
			}
			InternalEndSession();
		}

		d_OutputStream.open(filepath);

		if (d_OutputStream.is_open()) 
		{
			d_CurrentSession = new InstrumentationSession({ name });
			WriteHeader();
		}
		else 
		{
			if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			{ 
				DD_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
			}
		}
	}

	void Instrumentor::EndSession()
	{
		std::lock_guard lock(d_Mutex);
		InternalEndSession();
	}

	void Instrumentor::WriteProfile(const ProfileResult& result)
	{
		std::stringstream json;

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
		json << "\"name\":\"" << result.Name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.ThreadID << ",";
		json << "\"ts\":" << result.Start.count();
		json << "}";

		std::lock_guard lock(d_Mutex);
		if (d_CurrentSession) 
		{
			d_OutputStream << json.str();
			d_OutputStream.flush();
		}
	}

	void Instrumentor::WriteHeader()
	{
		d_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		d_OutputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		d_OutputStream << "]}";
		d_OutputStream.flush();
	}

	Instrumentor& Instrumentor::Instrumentor::Get()
	{
		static Instrumentor instance;
		return instance;
	}

	void Instrumentor::InternalEndSession()
	{
		if (d_CurrentSession)
		{
			WriteFooter();
			d_OutputStream.close();
			delete d_CurrentSession;
			d_CurrentSession = nullptr;
		}
	}

	InstrumentationTimer::InstrumentationTimer(const char* name)
		: d_Name(name), d_Stopped(false)
	{
		d_StartTimepoint = std::chrono::steady_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!d_Stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTimepoint = std::chrono::steady_clock::now();
		auto highResStart = FloatingPointMicroseconds{ d_StartTimepoint.time_since_epoch() };
		auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(d_StartTimepoint).time_since_epoch();
		
		Instrumentor::Get().WriteProfile({ d_Name, highResStart, elapsedTime, std::this_thread::get_id() });

		d_Stopped = true;
	}

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}
