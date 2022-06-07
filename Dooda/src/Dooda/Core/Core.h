#pragma once

#include <memory>

#include "PlatformDetection.h"

//TODO set up the readme page to download python and do everything correctly and move vulkan folder into better spot

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
#define DD_EXPAND_MACRO(x) x
#define DD_STRINGIFY_MACRO(x) #x

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

#include "Dooda/Core/Log.h"
#include "Dooda/Core/Assert.h"