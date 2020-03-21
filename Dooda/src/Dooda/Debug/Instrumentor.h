#pragma once

namespace Dooda 
{

	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor();

		void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		void EndSession();

		void WriteProfile(const ProfileResult& result);
		void WriteHeader();
		void WriteFooter();

	public: //Getters
		static Instrumentor& Get();

	private: //Variables
		InstrumentationSession* d_CurrentSession;
		std::ofstream d_OutputStream;
		int d_ProfileCount;

	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name);
		~InstrumentationTimer();

		void Stop();
		
	private: //Variables
		const char* d_Name;
		bool d_Stopped;

		std::chrono::time_point<std::chrono::high_resolution_clock> d_StartTimepoint;
	};
}

#define DD_PROFILE 1

#if DD_PROFILE
	#define DD_PROFILE_BEGIN_SESSION(name, filepath) ::Dooda::Instrumentor::Get().BeginSession(name, filepath)
	#define DD_PROFILE_END_SESSION() ::Dooda::Instrumentor::Get().EndSession()
	#define DD_PROFILE_SCOPE(name) ::Dooda::InstrumentationTimer timer##__LINE__(name);
	#define DD_PROFILE_FUNCTION() DD_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define DD_PROFILE_BEGIN_SESSION(name, filepath)
	#define DD_PROFILE_END_SESSION()
	#define DD_PROFILE_SCOPE(name)
	#define DD_PROFILE_FUNCTION()
#endif 