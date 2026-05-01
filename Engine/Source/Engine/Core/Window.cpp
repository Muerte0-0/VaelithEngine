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
	Ref<Window> Window::Create(const WindowSpecification& props)
	{
#ifdef PLATFORM_WINDOWS
		return CreateRef<WindowsWindow>(props);
#endif
#ifdef PLATFORM_LINUX
		return CreateRef<LinuxWindow>(props);
#endif
	}
}