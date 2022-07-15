#include "ddpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Dooda::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: d_WindowHandle(windowHandle)
{
	DD_CORE_ASSERT(d_WindowHandle, "Window handle is null")
}

Dooda::OpenGLContext::~OpenGLContext()
{
}

void Dooda::OpenGLContext::Init()
{
	DD_PROFILE_FUNCTION();

	glfwMakeContextCurrent(d_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	DD_CORE_ASSERT(status, "Failed to load Glad");

	DD_CORE_INFO("OpenGL Info");
	DD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	DD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	DD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	DD_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
}

void Dooda::OpenGLContext::SwapBuffers()
{
	DD_PROFILE_FUNCTION();

	glfwSwapBuffers(d_WindowHandle);
}
