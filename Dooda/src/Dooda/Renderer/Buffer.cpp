#include "ddpch.h"
#include "Buffer.h"

#include "Dooda/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Dooda
{

	Ref<VertexBuffer> VertexBuffer::Create(UINT size)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:	DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(size);
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* verticies, UINT size)
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
				return CreateRef<OpenGLVertexBuffer>(verticies, size);
			}
		}

		DD_CORE_ASSERT(false, "RendererAPI value is unknown!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(UINT* indicies, UINT size)
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
				return CreateRef<OpenGLIndexBuffer>(indicies, size);
			}
		}

		DD_CORE_ASSERT(false, "RendererAPI value is unknown!");
		return nullptr;
	}

}
