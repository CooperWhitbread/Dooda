#include "ddpch.h"
#include "Renderer.h"

#include "Dooda/Renderer/Renderer2D.h"

namespace Dooda
{
	Scope<Renderer::SceneData> Renderer::sd_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		DD_PROFILE_FUNCTION();

		RenderCommand::Init(); 
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(UINT width, UINT height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sd_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", sd_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}