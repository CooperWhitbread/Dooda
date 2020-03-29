#include "Ddpch.h"
#include "WindowsWindow.h"

#include "Dooda/Events/ApplicationEvent.h"
#include "Dooda/Events/KeyEvent.h"
#include "Dooda/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Dooda/Renderer/Renderer.h"

#include "Dooda/Core/Input.h"

namespace Dooda
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		DD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		DD_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		DD_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		DD_PROFILE_FUNCTION();

		d_Data.Title = props.Title;
		d_Data.Width = props.Width;
		d_Data.Height = props.Height;

		DD_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			DD_PROFILE_SCOPE("glfwInit");
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			DD_PROFILE_SCOPE("glfwCreateWindow");

			#if defined(DD_DEBUG)
				if (Renderer::GetCurrentRendererAPI() == RendererAPI::API::OpenGL)
					glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif

			d_Window = glfwCreateWindow((int)props.Width, (int)props.Height, d_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		d_Context = GraphicsContext::Create(d_Window);
		d_Context->Init();

		glfwSetWindowUserPointer(d_Window, &d_Data);
		SetVSync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(d_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(d_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(d_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(d_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(d_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(d_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(d_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		DD_PROFILE_FUNCTION();

		glfwDestroyWindow(d_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		DD_PROFILE_FUNCTION();

		glfwPollEvents();
		d_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		DD_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		d_Data.VSync = enabled;
	}

	bool WindowsWindow::GetVSync() const
	{
		return d_Data.VSync;
	}
}