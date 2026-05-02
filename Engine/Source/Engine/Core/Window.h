#pragma once
#include "Engine/Events/Event.h"

#include <string>
#include <functional>

struct GLFWwindow;

namespace Vaelith
{
	struct WindowSpecification
	{
		std::string Title = "Vaelith Engine";

		uint32_t Width = 1280;
		uint32_t Height = 720;

		bool CustomTitleBar = false;

		bool IsResizeable = true;
		bool LaunchMaximized = false;

		bool VSync = true;

		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn EventCallback;

		WindowSpecification() = default;

		WindowSpecification(const std::string& title, uint32_t width, uint32_t height)
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

		virtual GLFWwindow* GetHandle() const = 0;
		virtual void* GetNativeWindow() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void RaiseEvent(Event& event) = 0;

		virtual bool ShouldClose() const = 0;

		static Ref<Window> Create(const WindowSpecification& props = WindowSpecification());
	};
}