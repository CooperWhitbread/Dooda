#include "ddpch.h"
#include "WindowsWindow.h"

#include "Dooda/Core/Input.h"
#include "Dooda/Events/ApplicationEvent.h"
#include "Dooda/Events/KeyEvent.h"
#include "Dooda/Events/MouseEvent.h"
#include "Dooda/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

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
			DD_CORE_ASSERT(success, "Could not initialize GLFW!");
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

				WindowResizeEvent events(width, height);
				data.EventCallback(events);
			});

		glfwSetWindowCloseCallback(d_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent events;
				data.EventCallback(events);
			});

		glfwSetKeyCallback(d_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent events(key, false);
					data.EventCallback(events);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent events(key);
					data.EventCallback(events);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent events(key, true);
					data.EventCallback(events);
					break;
				}
				}
			});

		glfwSetCharCallback(d_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent events(keycode);
				data.EventCallback(events);
			});

		glfwSetMouseButtonCallback(d_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent events(button);
					data.EventCallback(events);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent events(button);
					data.EventCallback(events);
					break;
				}
				}
			});

		glfwSetScrollCallback(d_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent events((float)xOffset, (float)yOffset);
				data.EventCallback(events);
			});

		glfwSetCursorPosCallback(d_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent events((float)xPos, (float)yPos);
				data.EventCallback(events);
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