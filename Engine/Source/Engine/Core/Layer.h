#pragma once
#include "Base.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/Event.h"

namespace Vaelith
{
	class Scene;

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		
		virtual void OnEvent(Event& event) {}
		
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnFixedUpdate(Timestep deltaTime) {}

		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		
	private:
		std::string m_DebugName;
	};
}