#pragma once
#include "Engine/Core/Layer.h"

namespace Vaelith
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer() = default;
		virtual ~EditorLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(float DeltaTime) override;
		void OnFixedUpdate(float DeltaTime) override;

		void OnRender() override;
		void OnImGuiRender() override;

		void OnEvent(Event& event) override;
	};
}