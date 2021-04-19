#include "EditorLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Dooda {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), d_CameraController(1280.0f / 720.0f), d_SquareColor(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f })
	{
	}

	void EditorLayer::OnAttach()
	{
		DD_PROFILE_FUNCTION();

		d_CheckerboardTexture = Dooda::Texture2D::Create("assets/textures/Checkerboard.png");

		Dooda::FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		d_Framebuffer = Dooda::Framebuffer::Create(fbSpec);

		d_CameraController.SetZoomLevel(8.0f);
	}

	void EditorLayer::OnDetach()
	{
		DD_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Dooda::Timestep ts)
	{
		DD_PROFILE_FUNCTION();

		if (Dooda::FramebufferSpecification spec = d_Framebuffer->GetSpecification();
			d_ViewportSize.x > 0.0f && d_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != d_ViewportSize.x || spec.Height != d_ViewportSize.y))
		{
			d_Framebuffer->Resize((uint32_t)d_ViewportSize.x, (uint32_t)d_ViewportSize.y);
			d_CameraController.OnResize(d_ViewportSize.x, d_ViewportSize.y);
		}

		// Update
		if (d_ViewportFocused)
			d_CameraController.OnUpdate(ts);

		// Render
		Dooda::Renderer2D::ResetStats();
		{
			DD_PROFILE_SCOPE("Renderer Prep");
			d_Framebuffer->Bind();
			Dooda::RenderCommand::SetClearColor(glm::vec4{ 0.1f, 0.1f, 0.1f, 1 });
			Dooda::RenderCommand::Clear();
		}

		{
			static float rotation = 0.0f;
			rotation += ts * 50.0f;

			DD_PROFILE_SCOPE("Renderer Draw");
			Dooda::Renderer2D::BeginScene(d_CameraController.GetCamera());
			Dooda::Renderer2D::DrawRotatedQuad(glm::vec2{ 1.0f, 0.0f }, glm::vec2{ 0.8f, 0.8f }, -45.0f, glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
			Dooda::Renderer2D::DrawQuad(glm::vec2{ -1.0f, 0.0f }, glm::vec2{ 0.8f, 0.8f }, glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
			Dooda::Renderer2D::DrawQuad(glm::vec2{ 0.5f, -0.5f }, glm::vec2{ 0.5f, 0.75f }, d_SquareColor);
			Dooda::Renderer2D::DrawQuad(glm::vec3{ 0.0f, 0.0f, -0.1f }, glm::vec2{ 20.0f, 20.0f }, d_CheckerboardTexture, 10.0f);
			Dooda::Renderer2D::DrawRotatedQuad(glm::vec3{ -2.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f }, rotation, d_CheckerboardTexture, 20.0f);
			Dooda::Renderer2D::EndScene();

			Dooda::Renderer2D::BeginScene(d_CameraController.GetCamera());
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = glm::vec4{ (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					Dooda::Renderer2D::DrawQuad(glm::vec2{ x, y }, glm::vec2{ 0.45f, 0.45f }, color);
				}
			}
			Dooda::Renderer2D::EndScene();
			d_Framebuffer->Unbind();
		}
	}

	void EditorLayer::OnImGuiRender()
	{
		DD_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Dooda::Application::Get().Close();
				ImGui::EndMenu();

			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Dooda::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(d_SquareColor));

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		d_ViewportFocused = ImGui::IsWindowFocused();
		d_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!d_ViewportFocused || !d_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		d_ViewportSize = glm::vec2{ viewportPanelSize.x, viewportPanelSize.y };
		uint32_t textureID = d_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ d_ViewportSize.x, d_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Dooda::Event& e)
	{
		d_CameraController.OnEvent(e);
	}

}