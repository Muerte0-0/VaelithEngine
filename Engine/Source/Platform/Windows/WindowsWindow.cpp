#include "vltpch.h"
#include "WindowsWindow.h"
#include "Engine/Events/WindowEvents.h"

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

	void WindowsWindow::OnUpdate(Timestep deltaTime)
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

		// Store pointer to m_Data so the callback can reach it without capturing
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			data.Width  = static_cast<uint32_t>(width);
			data.Height = static_cast<uint32_t>(height);

			if (data.EventCallback)
			{
				WindowResizeEvent event(data.Width, data.Height);
				data.EventCallback(event);
			}
		});

		LOG(LogLevel::Info,"Created Window: {}", m_Data.Title);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}