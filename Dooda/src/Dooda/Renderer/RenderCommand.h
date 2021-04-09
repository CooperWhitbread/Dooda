#pragma once

#include "Dooda/Renderer/RendererAPI.h"

namespace Dooda {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			sd_RendererAPI->Init();
		}

		inline static void Clear()
		{
			sd_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, UINT count = 0)
		{
			sd_RendererAPI->DrawIndexed(vertexArray, count);
		}

	public: //Setters
		inline static void SetViewport(UINT x, UINT y, UINT width, UINT height)
		{
			sd_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			sd_RendererAPI->SetClearColor(color);
		}

	private: //Variables
		static Scope<RendererAPI> sd_RendererAPI;
	};

}