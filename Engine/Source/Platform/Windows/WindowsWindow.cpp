#include "vltpch.h"
#include "WindowsWindow.h"

namespace Vaelith
{
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& props) : m_Data(props)
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

	void WindowsWindow::Init(const WindowProps& props)
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

		std::cout << "Created Windows window: " << m_Data.Title << "\n";
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}