#include "Ddpch.h"
#include "Input.h"

#ifdef DD_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Dooda 
{

	Scope<Input> Input::sd_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef DD_PLATFORM_WINDOWS
				return CreateScope<WindowsInput>();
		#else
			DD_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}