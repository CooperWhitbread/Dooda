#include "ddpch.h"
#include "Texture.h"

#include "Dooda/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Dooda {

	Ref<Texture2D> Texture2D::Create(UINT width, UINT height)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:	DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:	DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}