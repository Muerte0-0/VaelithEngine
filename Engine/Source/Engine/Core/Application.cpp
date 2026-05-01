#include "vltpch.h"
#include "Application.h"

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
    }

    void Application::Shutdown()
    {
		Stop();

		m_Window = nullptr;

        for (auto& layer : std::views::reverse(m_LayerStack))
            layer->OnDetach();

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
			const float deltaTime = glm::clamp(currentTime - lastTime, MIN_DELTA_TIME, MAX_DELTA_TIME);
			lastTime = currentTime;

			accumulator += deltaTime;

			// Fixed update
			while (accumulator >= FIXED_FRAME_TIME)
			{
				if (!m_IsMinimized)
				{
					//m_ImGuiLayer->OnFixedUpdate(FIXED_FRAME_TIME);

					for (const auto& layer : m_LayerStack)
						layer->OnFixedUpdate(FIXED_FRAME_TIME);
				}
				accumulator -= FIXED_FRAME_TIME;
			}

			// Per-frame update
			if (!m_IsMinimized)
			{
				//m_ImGuiLayer->OnUpdate(deltaTime);
				std::vector<Layer*> layers;
				layers.reserve(m_LayerStack.size());
				for (const auto& l : m_LayerStack)
					layers.push_back(l.get());

				//Renderer::BeginScene();

				for (const auto& layer : m_LayerStack)
					layer->OnRender();

				//m_ImGuiLayer->OnRender();

				//m_ImGuiLayer->Begin(deltaTime);

				//Renderer::DrawFrame();
				
				//m_ImGuiLayer->OnImGuiRender();

				for (const auto& layer : m_LayerStack)
					layer->OnImGuiRender();
				

				//m_ImGuiLayer->End();

				m_Window->OnUpdate();
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
	{}

	float Application::GetTime()
	{
		return glfwGetTime();
	}
}