#pragma once
#include "Engine.h"

namespace Vaelith
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer() = default;
		virtual ~EditorLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep DeltaTime) override;
		void OnFixedUpdate(Timestep DeltaTime) override;

		void OnRender() override;
		void OnImGuiRender() override;

		void OnEvent(Event& event) override;
	};
}