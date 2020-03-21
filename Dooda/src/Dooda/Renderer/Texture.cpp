#include "Ddpch.h"
#include "Texture.h"

#include "Dooda/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Dooda {

	Ref<Texture2DManager> s_Texture2DManager = std::make_shared<OpenGLTexture2DManager>();
	
	/*Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}*/

	void Texture2DManager::Create()
	{
		/*switch (Renderer::GetCurrentRendererAPI())
		{
		case RendererAPI::API::None:
		{
			DD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
		}
		case RendererAPI::API::OpenGL:
		{
			//s_Texture2DManager = CreateRef<OpenGLTexture2DManager>();
		}
		}

		DD_CORE_ASSERT(false, "Unknown RendererAPI!");*/
	}

}