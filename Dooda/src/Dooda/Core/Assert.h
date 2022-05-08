#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Core/Log.h"

#include <filesystem>

#ifdef DD_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define DD_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { DD##type##ERROR(msg, __VA_ARGS__); DD_DEBUGBREAK(); } }
#define DD_INTERNAL_ASSERT_WITH_MSG(type, check, ...) DD_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define DD_INTERNAL_ASSERT_NO_MSG(type, check) DD_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", DD_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define DD_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define DD_INTERNAL_ASSERT_GET_MACRO(...) DD_EXPAND_MACRO( DD_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, DD_INTERNAL_ASSERT_WITH_MSG, DD_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define DD_ASSERT(...) DD_EXPAND_MACRO( DD_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define DD_CORE_ASSERT(...) DD_EXPAND_MACRO( DD_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define DD_ASSERT(...)
#define DD_CORE_ASSERT(...)
#endif
