#include "Ddpch.h"
#include "GraphicsContext.h"

#include "Dooda/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Dooda
{

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:    DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
