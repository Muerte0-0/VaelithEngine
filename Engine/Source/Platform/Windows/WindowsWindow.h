#pragma once
#include "Engine/Core/Window.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Vaelith
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& props);
		virtual ~WindowsWindow();

		void OnUpdate(Timestep deltaTime) override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		GLFWwindow* GetHandle() const override { return m_Window; }
		void* GetNativeWindow() const override { return glfwGetWin32Window(m_Window); }

		void SetVSync(bool enabled) override { m_Data.VSync = enabled; }
		bool IsVSync() const override { return m_Data.VSync; }

		bool ShouldClose() const override { return glfwWindowShouldClose(m_Window) != 0; }

	private:
		void Init(const WindowSpecification& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window;

		WindowSpecification m_Data;
	
	};
}