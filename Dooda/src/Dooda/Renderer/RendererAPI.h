#pragma once

#include "Dooda/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Dooda 
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(UINT x, UINT y, UINT width, UINT height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, UINT indexCount = 0) = 0;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, UINT vertexCount) = 0;

		virtual void SetLineWidth(float width) = 0;

	public: //Getters
		inline static API GetAPI() { return sd_API; }

	public: //Static Functions
		static Scope<RendererAPI> SD_Create();

	private: //Variables
		static API sd_API;
	};

}