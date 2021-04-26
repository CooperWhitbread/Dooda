#pragma once

#include <memory>

#include "PlatformDetection.h"

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
#define DD_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
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