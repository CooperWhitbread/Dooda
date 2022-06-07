#include "ddpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

#include "Dooda/Renderer/Renderer.h"

namespace Dooda
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::sd_Instance = nullptr;

	Application::Application(const std::string& name, ApplicationCommandLineArgs args)
		: d_CommandLineArgs(args)
	{
		DD_PROFILE_FUNCTION();

		DD_CORE_ASSERT(!sd_Instance, "Application already exists!");
		sd_Instance = this;

		d_Window = Window::SD_Create(WindowProps(name));
		d_Window->SetEventCallback(DD_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		d_ImGuiLayer = new ImGuiLayer();
		PushOverlay(d_ImGuiLayer);

	}

	Application::~Application()
	{
		DD_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}


	void Dooda::Application::Run()
	{
		DD_PROFILE_FUNCTION();

		while (d_Running)
		{
			DD_PROFILE_SCOPE("RunLoop");
			auto time = (float)glfwGetTime(); //Platform::GetTime();
			Timestep timestep = time - d_LastFrameTime;
			d_LastFrameTime = time;

			if (!d_Minimized)
			{
				{
					DD_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : d_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}

				d_ImGuiLayer->Begin();
				{
					DD_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : d_LayerStack)
					{
						layer->OnImGuiRender();
					}
				}
				d_ImGuiLayer->End();
			}


			d_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		d_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		DD_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DD_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(DD_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = d_LayerStack.rbegin(); it != d_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		DD_PROFILE_FUNCTION();

		d_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		DD_PROFILE_FUNCTION();

		d_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		d_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		DD_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			d_Minimized = true;
			return false;
		}

		d_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}