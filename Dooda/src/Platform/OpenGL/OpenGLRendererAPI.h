#pragma once

#include "Dooda/Renderer/RendererAPI.h"

namespace Dooda {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override; 

		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, UINT indexCount = 0) override;

	public: //Setters
		virtual void SetViewport(UINT x, UINT y, UINT width, UINT height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
	};


}