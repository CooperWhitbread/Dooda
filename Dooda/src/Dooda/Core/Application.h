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

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			DD_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class Application
	{
	public:
		Application(const std::string& name = "Dooda Application", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		ImGuiLayer* GetImGuiLayer() { return d_ImGuiLayer; }
		ApplicationCommandLineArgs GetCommandLineArgs() const { return d_CommandLineArgs; }

	public: //Getters
		inline static Application& Get() { return *sd_Instance; }
		inline Window& GetWindow() { return *d_Window; }

		void Close();

	private: //Private Functions
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private: //Variables
		ApplicationCommandLineArgs d_CommandLineArgs;
		Scope<Window> d_Window;

		ImGuiLayer* d_ImGuiLayer;
		bool d_Minimized = false;
		bool d_Running = true;
		LayerStack d_LayerStack;

		float d_LastFrameTime = 0.0f;

	private:
		static Application* sd_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* S_CreateApplication(ApplicationCommandLineArgs args);

}
