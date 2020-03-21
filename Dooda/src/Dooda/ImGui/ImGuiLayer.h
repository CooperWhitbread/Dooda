#pragma once

#include "Dooda/Core/Layer.h"

#include "Dooda/Events/KeyEvent.h"
#include "Dooda/Events/MouseEvent.h"
#include "Dooda/Events/ApplicationEvent.h"

namespace Dooda
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private: //Variables
		float d_Time = 0.0f;
	};

}