#include "Ddpch.h"
#include "Instrumentor.h"

namespace Dooda
{
	Instrumentor::Instrumentor()
		: d_CurrentSession(nullptr), d_ProfileCount(0)
	{
	}

	void Instrumentor::BeginSession(const std::string& name, const std::string& filepath)
	{
		d_OutputStream.open(filepath);
		WriteHeader();
		d_CurrentSession = new InstrumentationSession{ name };
	}

	void Instrumentor::EndSession()
	{
		WriteFooter();
		d_OutputStream.close();
		d_CurrentSession = nullptr;
		d_ProfileCount = 0;
	}

	void Instrumentor::WriteProfile(const ProfileResult& result)
	{
		if (d_ProfileCount++ > 0)
		{
			d_OutputStream << ",";
		}

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		d_OutputStream << "{";
		d_OutputStream << "\"cat\":\"function\",";
		d_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
		d_OutputStream << "\"name\":\"" << name << "\",";
		d_OutputStream << "\"ph\":\"X\",";
		d_OutputStream << "\"pid\":0,";
		d_OutputStream << "\"tid\":" << result.ThreadID << ",";
		d_OutputStream << "\"ts\":" << result.Start;
		d_OutputStream << "}";

		d_OutputStream.flush();
	}

	void Instrumentor::WriteHeader()
	{
		d_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
		d_OutputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		d_OutputStream << "]}";
		d_OutputStream.flush();
	}

	Instrumentor& Instrumentor::Get()
	{
		static Instrumentor instance;
		return instance;
	}

	InstrumentationTimer::InstrumentationTimer(const char* name)
		: d_Name(name), d_Stopped(false)
	{
		d_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!d_Stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(d_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		uint32_t threadID = (uint32_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
		Instrumentor::Get().WriteProfile({ d_Name, start, end, threadID });

		d_Stopped = true;
	}

}
