#include "ddpch.h"
#include "Window.h"

#ifdef DD_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Dooda
{

	Scope<Window> Window::SD_Create(const WindowProps& props)
	{
		#ifdef DD_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			DD_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}