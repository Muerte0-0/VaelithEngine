#include "vltpch.h"
#include "Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#endif // PLATFORM_LINUX



namespace Vaelith
{
	Window* Window::Create (const WindowProps& props)
	{
#ifdef PLATFORM_WINDOWS
		return new WindowsWindow(props);
#endif
#ifdef PLATFORM_LINUX
		return new LinuxWindow (props);
#endif
	}
}