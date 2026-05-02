#pragma once
#include "Engine/Core/Layer.h"

namespace Vaelith
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() = default;
		virtual ~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
		void FlushWindowOps(); // Call immediately after Renderer::EndFrame() / bgfx::frame()

		virtual void OnImGuiRender() override;
	};
}