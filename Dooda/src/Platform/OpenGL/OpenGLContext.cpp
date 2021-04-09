#include "Ddpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

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

	//Add when opengl version is 4.5 or higher
	/*#ifdef DD_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		DD_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Dooda requires at least OpenGL version 4.5!");
	#endif*/
}

void Dooda::OpenGLContext::SwapBuffers()
{
	DD_PROFILE_FUNCTION();

	glfwSwapBuffers(d_WindowHandle);
}
