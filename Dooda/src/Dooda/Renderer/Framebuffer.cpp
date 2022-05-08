#include "ddpch.h"
#include "Framebuffer.h"

#include "Dooda/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Dooda {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:    DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}