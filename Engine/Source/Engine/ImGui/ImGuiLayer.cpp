#include "vltpch.h"
#include "ImGuiLayer.h"

#include "Engine/Core/Application.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/RenderCommand.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include "backends/imgui_impl_bgfx.h"

namespace Vaelith
{
	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui Context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;			// Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;			// Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;				// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;				// Enable Viewports
		io.ConfigFlags |= ImGuiConfigFlags_IsSRGB;						// Enable SRGB for ImGui

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetHandle());
		ImGui_ImplGlfw_InitForOther(window, true);
		ImGui_Implbgfx_Init(UIPASS_VIEW_ID);
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_Implbgfx_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_Implbgfx_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();

		ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void ImGuiLayer::FlushWindowOps()
	{
		ImGui_Implbgfx_FlushWindowOps();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		ImGui::ShowDemoWindow();
	}
}