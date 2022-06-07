#include "ddpch.h"
#include "UniformBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Dooda {

	Ref<UniformBuffer> UniformBuffer::Create(UINT size, UINT binding)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:    DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
