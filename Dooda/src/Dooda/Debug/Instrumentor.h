#pragma once

#include <iomanip>

namespace Dooda 
{

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
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

	public: //Getters
		static Instrumentor& Get();

	private: //Private Functions
		void WriteHeader();
		void WriteFooter();

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession();

	private: //Variables
		std::mutex d_Mutex;
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

		std::chrono::time_point<std::chrono::steady_clock> d_StartTimepoint;
	};
}

#define DD_PROFILE 0

#if DD_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define DD_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define DD_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define DD_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define DD_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define DD_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define DD_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define DD_FUNC_SIG __func__
	#else
		#define DD_FUNC_SIG "DD_FUNC_SIG unknown!"
	#endif

	#define DD_PROFILE_BEGIN_SESSION(name, filepath) ::Dooda::Instrumentor::Get().BeginSession(name, filepath)
	#define DD_PROFILE_END_SESSION() ::Dooda::Instrumentor::Get().EndSession()
	#define DD_PROFILE_SCOPE(name) constexpr auto fixedName = ::Dooda::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
									::Dooda::InstrumentationTimer timer##__LINE__(fixedName.Data)
	#define DD_PROFILE_FUNCTION() DD_PROFILE_SCOPE(DD_FUNC_SIG)

#else
	#define DD_PROFILE_BEGIN_SESSION(name, filepath)
	#define DD_PROFILE_END_SESSION()
	#define DD_PROFILE_SCOPE(name)
	#define DD_PROFILE_FUNCTION()
#endif 