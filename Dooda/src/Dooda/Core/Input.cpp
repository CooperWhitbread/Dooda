#include "Ddpch.h"
#include "Input.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Dooda 
{

	Scope<Input> Input::sd_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef HZ_PLATFORM_WINDOWS
				return CreateScope<WindowsInput>();
		#else
			HZ_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}