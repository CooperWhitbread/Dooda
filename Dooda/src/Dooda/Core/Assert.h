#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Core/Log.h"

#ifdef DD_ENABLE_ASSERTS

namespace Dooda::Assert
{
	// Returns the simple file name rather than full path as suggested by LovelySanta
	constexpr const char* CurrentFileName(const char* path) {
		const char* file = path;
		while (*path)
		{
			if (*path == '/' || *path == '\\')
				file = ++path;
			else
				path++;
		}
		return file;
	}
}

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define DD_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { DD##type##ERROR(msg, __VA_ARGS__); DD_DEBUGBREAK(); } }
#define DD_INTERNAL_ASSERT_WITH_MSG(type, check, ...) DD_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define DD_INTERNAL_ASSERT_NO_MSG(type, check) DD_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", DD_STRINGIFY_MACRO(check), ::Hazel::Assert::CurrentFileName(__FILE__), __LINE__)

#define DD_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define DD_INTERNAL_ASSERT_GET_MACRO(...) DD_EXPAND_MACRO( DD_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, DD_INTERNAL_ASSERT_WITH_MSG, DD_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define DD_ASSERT(...) DD_EXPAND_MACRO( DD_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define DD_CORE_ASSERT(...) DD_EXPAND_MACRO( DD_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define DD_ASSERT(...)
#define DD_CORE_ASSERT(...)
#endif
