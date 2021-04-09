#pragma once

#include <memory>

///////////////////////////////////////////////
// Platform detection using predefined macros//
///////////////////////////////////////////////
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define DD_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define DD_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define DD_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else 
		#error "Unknown Apple platform!"
	#endif

 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define DD_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define DD_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif

////////////////////
//Debugging Macros//
////////////////////
#ifdef DD_DEBUG
	#if defined(DD_PLATFORM_WINDOWS)
		#define DD_DEBUGBREAK() __debugbreak()
	#elif defined(DD_PLATFORM_LINUX)
		#include <signal.h>
		#define DD_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define DD_ENABLE_ASSERTS
	#else
	#define DD_DEBUGBREAK()
#endif

#ifdef DD_ENABLE_ASSERTS
	#define DD_ASSERT(x, ...) { if(!(x)) { DD_ERROR("Assertion Failed: {0}", __VA_ARGS__); DD_DEBUGBREAK(); } }
	#define DD_CORE_ASSERT(x, ...) { if(!(x)) { DD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); DD_DEBUGBREAK(); } }
	#else
	#define DD_ASSERT(x, ...)
	#define DD_CORE_ASSERT(x, ...)
#endif

////////////////////
//Useful Functions//
////////////////////
#define BIT(x) (1 << x)
#define DD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define UINT UINT
#define INT int32_t

/////////////
//templates//
/////////////
namespace Dooda {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}