#pragma once

#include "Dooda/Core/Timestep.h"
#include "Dooda/Events/Event.h"

namespace Dooda
{

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

	public: //Getters
		inline const std::string& GetName() const { return d_DebugName; }

	protected: //Variables
		std::string d_DebugName;
	};
}