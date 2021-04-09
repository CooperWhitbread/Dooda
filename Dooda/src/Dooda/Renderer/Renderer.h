#pragma once

#include "Dooda/Renderer/RenderCommand.h"

#include "Dooda/Renderer/OrthographicCamera.h"
#include "Dooda/Renderer/Shader.h"

namespace Dooda
{

	class Renderer
	{
	public:
		static void Init(); 
		static void Shutdown();

		static void OnWindowResize(UINT width, UINT height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

	public: //Getters
		inline static RendererAPI::API GetCurrentRendererAPI() { return RendererAPI::GetAPI(); }

	private: //Variables
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> sd_SceneData;
	};

}