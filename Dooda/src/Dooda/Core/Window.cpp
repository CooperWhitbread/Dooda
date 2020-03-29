#include "Ddpch.h"
#include "Window.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Dooda
{

	Scope<Window> Window::SD_Create(const WindowProps& props)
	{
		#ifdef HZ_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			HZ_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}