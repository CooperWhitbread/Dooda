#pragma once

#include "Dooda/Events/Event.h"
#include "Dooda/Events/ApplicationEvent.h"
#include "Dooda/Core/LayerStack.h"
#include "Dooda/Core/Window.h"

#include "Dooda/ImGui/ImGuiLayer.h"

#include "Dooda/Core/Timestep.h"

int main(int argc, char** argv);

namespace Dooda
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	public: //Getters
		inline static Application& Get() { return *sd_Instance; }
		inline Window& GetWindow() { return *d_window; }

	private: //Private Functions
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private: //Variables
		std::unique_ptr<Window> d_window;

		ImGuiLayer* d_imGuiLayer;
		bool m_Minimized = false;
		bool d_running = true;
		LayerStack d_layerStack;

		float d_lastFrameTime = 0.0f;

	private:
		static Application* sd_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* S_CreateApplication();

}