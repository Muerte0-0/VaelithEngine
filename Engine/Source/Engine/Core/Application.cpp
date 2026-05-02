#include "vltpch.h"
#include "Application.h"
#include "Engine/Renderer/Renderer.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

constexpr float MIN_DELTA_TIME = 0.001f;
constexpr float MAX_DELTA_TIME = 0.1f;
constexpr float FIXED_FRAME_TIME = 1.0f / 60.0f;

extern bool g_ApplicationRunning;

namespace Vaelith
{
    static Application* s_Application = nullptr;

    static void GLFWErrorCallback(int error, const char* description)
    {
        std::cerr << "[GLFW Error]: " << description << '\n';
    }

    Application::Application()
    {
        s_Application = this;
    }

    Application::~Application()
    {
		s_Application = nullptr;
    }

    void Application::Initialize()
    {
        glfwSetErrorCallback(GLFWErrorCallback);
        glfwInit();

        WindowSpecification spec = GetApplicationSpecs().WindowSpec;
        spec.EventCallback = [this](Event& event) { RaiseEvent(event); };

        m_Window = Window::Create(spec);

		RendererConfig config;
		config.NativeWindowHandle = m_Window->GetNativeWindow();
		config.Width = m_Window->GetWidth();
		config.Height = m_Window->GetHeight();
		config.VSync = m_Window->IsVSync();

		Renderer::Init(config);

		m_ImGuiLayer = CreateScope<ImGuiLayer>();
		m_ImGuiLayer->OnAttach();

		for (auto& layer : m_LayerStack)
			layer->OnAttach();
    }

    void Application::Shutdown()
    {
		Renderer::Shutdown();

		m_ImGuiLayer->OnDetach();

        for (auto& layer : std::views::reverse(m_LayerStack))
            layer->OnDetach();

		m_Window = nullptr;

        glfwTerminate();
    }

    void Application::Run()
    {
		g_ApplicationRunning = true;

		float lastTime = GetTime();
		float accumulator = 0.0f;

		while (g_ApplicationRunning)
		{
			glfwPollEvents();

			if (m_Window->ShouldClose())
			{
				Stop();
				break;
			}

			const float currentTime = static_cast<float>(glfwGetTime());
			const Timestep deltaTime = glm::clamp(currentTime - lastTime, MIN_DELTA_TIME, MAX_DELTA_TIME);
			lastTime = currentTime;

			accumulator += deltaTime;

			// Fixed update
			while (accumulator >= FIXED_FRAME_TIME)
			{
				if (!m_IsMinimized)
				{
					m_ImGuiLayer->OnFixedUpdate(FIXED_FRAME_TIME);

					for (const auto& layer : m_LayerStack)
						layer->OnFixedUpdate(FIXED_FRAME_TIME);
				}
				accumulator -= FIXED_FRAME_TIME;
			}

			// Per-frame update
			if (!m_IsMinimized)
			{
				m_ImGuiLayer->OnUpdate(deltaTime);
				std::vector<Layer*> layers;

				layers.reserve(m_LayerStack.size());
				for (const auto& l : m_LayerStack)
					layers.push_back(l.get());

				Renderer::BeginFrame();

				for (const auto& layer : m_LayerStack)
					layer->OnRender();

				m_ImGuiLayer->OnRender();

				m_ImGuiLayer->Begin();
				
				m_ImGuiLayer->OnImGuiRender();

				for (const auto& layer : m_LayerStack)
					layer->OnImGuiRender();
				
				m_ImGuiLayer->End();

				Renderer::EndFrame();

				m_ImGuiLayer->FlushWindowOps();

				m_Window->OnUpdate(deltaTime);
			}

			const float sleepTime = FIXED_FRAME_TIME - (GetTime() - currentTime);
			if (sleepTime > 0)
				std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
		}
    }

    void Application::Stop()
    {
		g_ApplicationRunning = false;
    }

	void Application::RaiseEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(&Application::OnWindowResize));
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(&Application::OnWindowClosed));
		
		m_ImGuiLayer->OnEvent(event);

		if (event.Handled)
			return;

		for (auto& layer : std::views::reverse(m_LayerStack))
		{
			layer->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	Application& Application::Get()
	{
		return *s_Application;
	}

	float Application::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		const uint32_t w = e.GetWidth();
		const uint32_t h = e.GetHeight();

		if (w == 0 || h == 0)
		{
			m_IsMinimized = true;
			return false;
		}

		m_IsMinimized = false;
		Renderer::OnWindowResize(w, h);

		ImGui::GetIO().DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));

		return false;
	}

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		Stop();

		return true;
	}
}