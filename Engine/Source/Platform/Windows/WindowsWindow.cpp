#include "vltpch.h"
#include "WindowsWindow.h"

namespace Vaelith
{
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowSpecification& props) : m_Data(props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::Init(const WindowSpecification& props)
	{
		if (!s_GLFWInitialized)
		{
			glfwInit();
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_Window = glfwCreateWindow(
			(int) props.Width,
			(int) props.Height,
			m_Data.Title.c_str(),
			nullptr,
			nullptr
		);

		LOG(LogLevel::Info,"Created Window: {}", m_Data.Title);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::RaiseEvent(Event& event)
	{}
}