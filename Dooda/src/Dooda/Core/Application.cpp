#include "Ddpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

#include "Dooda/Renderer/Renderer.h"

namespace Dooda
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::sd_Instance = nullptr;

	Application::Application()
	{
		DD_PROFILE_FUNCTION();

		DD_CORE_ASSERT(!sd_Instance, "Application already exists!");
		sd_Instance = this;

		d_window = Window::SD_Create();
		d_window->SetEventCallback(DD_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		d_imGuiLayer = new ImGuiLayer();
		PushOverlay(d_imGuiLayer);

	}

	Application::~Application()
	{
		DD_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}


	void Dooda::Application::Run()
	{
		DD_PROFILE_FUNCTION();

		while (d_running)
		{
			DD_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime(); //Platform::GetTime();
			Timestep timestep = time - d_lastFrameTime;
			d_lastFrameTime = time;

			if (!m_Minimized)
			{
				{
					DD_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : d_layerStack)
					{
						layer->OnUpdate(timestep);
					}
				}

				d_imGuiLayer->Begin();
				{
					DD_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : d_layerStack)
					{
						layer->OnImGuiRender();
					}
				}
				d_imGuiLayer->End();
			}


			d_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		DD_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DD_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(DD_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = d_layerStack.rbegin(); it != d_layerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		DD_PROFILE_FUNCTION();

		d_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		DD_PROFILE_FUNCTION();

		d_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		d_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		DD_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}