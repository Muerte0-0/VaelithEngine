#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <functional>

namespace Vaelith
{
	struct WindowProps
	{
		std::string Title = "Vaelith Engine";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool CustomTitleBar = false;
		bool IsResizeable = true;
		bool LaunchMaximized = false;
		bool VSync = true;

		using EventCallbackFn = std::function<void()>;
		EventCallbackFn EventCallback;

		WindowProps() = default;

		WindowProps(const std::string& title, uint32_t width, uint32_t height)
			: Title(title), Width(width), Height(height)
		{}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}