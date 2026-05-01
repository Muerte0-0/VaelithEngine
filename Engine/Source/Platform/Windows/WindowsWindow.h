#pragma once
#include "Engine/Core/Window.h"

namespace Vaelith
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		GLFWwindow* GetHandle() const override { return m_Window; }
		void* GetNativeWindow() const override { return m_Window; }

		void SetVSync(bool enabled) override { m_Data.VSync = enabled; }
		bool IsVSync() const override { return m_Data.VSync; }

		void RaiseEvent(Event& event) override;
		bool ShouldClose() const override { return glfwWindowShouldClose(m_Window) != 0; }

	private:
		void Init(const WindowSpecification& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window;

		WindowSpecification m_Data;
	
	};
}