#include "Ddpch.h"

#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dooda {

	RendererAPI::API RendererAPI::sd_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::SD_Create()
	{
		switch (sd_API)
		{
		case RendererAPI::API::None:    DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}