#include "ddpch.h"
#include "VertexArray.h"

#include "Dooda/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dooda {

	Ref<VertexArray> VertexArray::SD_Create()
	{
		switch (Renderer::GetCurrentRendererAPI())
			{
			case RendererAPI::API::None:
			{
				DD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:  
			{
				return CreateRef<OpenGLVertexArray>();
			}
		}

		DD_CORE_ASSERT(false, "RendererAPI value is unknown!");
		return nullptr;
	}

}
