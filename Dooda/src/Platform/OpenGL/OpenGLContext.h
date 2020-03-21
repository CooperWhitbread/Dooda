#pragma once

#include "Dooda/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dooda
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* d_WindowHandle;

	};

}