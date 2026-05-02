#include "vltpch.h"
#include "WindowsWindow.h"

#include "Engine/Events/WindowEvents.h"
#include "Engine/Events/InputEvents.h"

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

		// ---------------------------------------------------------------
		// GLFW callbacks
		// ---------------------------------------------------------------

		if (m_Data.EventCallback)
		{
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* handle)
			{
				auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(handle));
				WindowClosedEvent event;
				data.EventCallback(event);
			});

			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* handle, int width, int height)
			{
				auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(handle));
				WindowResizeEvent event(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
				data.EventCallback(event);
			});

			glfwSetKeyCallback(m_Window, [](GLFWwindow* handle, int key, int /*scancode*/, int action, int /*mods*/)
			{
				auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(handle));
				switch (action)
				{
					case GLFW_PRESS:
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, action == GLFW_REPEAT);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					default: break;
				}
			});

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* handle, int button, int action, int /*mods*/)
			{
				auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(handle));
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
					default: break;
				}
			});

			glfwSetScrollCallback(m_Window, [](GLFWwindow* handle, double xOffset, double yOffset)
			{
				auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(handle));
				MouseScrolledEvent event(xOffset, yOffset);
				data.EventCallback(event);
			});

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* handle, double x, double y)
			{
				auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(handle));
				MouseMovedEvent event(x, y);
				data.EventCallback(event);
			});
		}

		LOG(LogLevel::Info,"Created Window: {}", m_Data.Title);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}