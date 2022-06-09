#include "EditorLayer.h"

#include "Dooda/Scene/SceneSerialiser.h"
#include "Dooda/Utilities/PlatformUtilities.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ImGuizmo.h>

#include "Dooda/Math/Math.h"

namespace Dooda 
{

	extern const std::filesystem::path g_AssetPath;

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), d_CameraController(1280.0f / 720.0f), d_SquareColor(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f })
	{
	}

	void EditorLayer::OnAttach()
	{
		DD_PROFILE_FUNCTION();

		d_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8,FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		d_Framebuffer = Framebuffer::Create(fbSpec);

		d_ActiveScene = CreateRef<Scene>();

		auto commandLineArgs = Application::Get().GetCommandLineArgs();
		if (commandLineArgs.Count > 1)
		{
			auto sceneFilePath = commandLineArgs[1];
			SceneSerialiser serialiser(d_ActiveScene);
			serialiser.Deserialise(sceneFilePath);
		}

		d_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
		d_SceneHierarchyPanel.SetContext(d_ActiveScene);
		//d_CameraController.SetZoomLevel(8.0f);
	}

	void EditorLayer::OnDetach()
	{
		DD_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		DD_PROFILE_FUNCTION();

		if (FramebufferSpecification spec = d_Framebuffer->GetSpecification();
			d_ViewportSize.x > 0.0f && d_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != d_ViewportSize.x || spec.Height != d_ViewportSize.y))
		{
			d_Framebuffer->Resize((UINT)d_ViewportSize.x, (UINT)d_ViewportSize.y);
			d_CameraController.OnResize(d_ViewportSize.x, d_ViewportSize.y);
			d_EditorCamera.SetViewportSize(d_ViewportSize.x, d_ViewportSize.y);
			d_ActiveScene->OnViewportResize((UINT)d_ViewportSize.x, (UINT)d_ViewportSize.y);
		}

		// Update
		if (d_ViewportFocused)
			d_CameraController.OnUpdate(ts);
		d_EditorCamera.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		d_Framebuffer->Bind();
		RenderCommand::SetClearColor(glm::vec4{ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		// Clear our entity ID attachment to -1
		d_Framebuffer->ClearColourAttachment(1, -1);

		// Update scene
		d_ActiveScene->OnUpdateEditor(ts, d_EditorCamera);

		auto [mx, my] = ImGui::GetMousePos();
		mx -= d_ViewportBounds[0].x;
		my -= d_ViewportBounds[0].y;
		glm::vec2 viewportSize = d_ViewportBounds[1] - d_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = d_Framebuffer->ReadPixel(1, mouseX, mouseY);
			d_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, d_ActiveScene.get());
		}


		d_Framebuffer->Unbind();
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
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();
				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				ImGui::EndMenu();

			}

			ImGui::EndMenuBar();
		}

		d_SceneHierarchyPanel.OnImGuiRender();
		d_ContentBrowserPanel.OnImGuiRender();

		ImGui::Begin("Stats");

		std::string name = "None";
		if (d_HoveredEntity)
			name = d_HoveredEntity.GetComponent<TagComponent>().Tag;
		ImGui::Text("Hovered Entity: %s", name.c_str());

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		//setting vewport boding box
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		d_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		d_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		d_ViewportFocused = ImGui::IsWindowFocused();
		d_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!d_ViewportFocused && !d_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		d_ViewportSize = glm::vec2(viewportPanelSize.x, viewportPanelSize.y);

		uint64_t textureID = d_Framebuffer->GetColorAttachmentRendererID(0);
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ d_ViewportSize.x, d_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				OpenScene(std::filesystem::path(g_AssetPath) / path);
			}
			ImGui::EndDragDropTarget();
		}

		// Gizmos
		Entity selectedEntity = d_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && d_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(d_ViewportBounds[0].x, d_ViewportBounds[0].y, d_ViewportBounds[1].x - d_ViewportBounds[0].x, d_ViewportBounds[1].y - d_ViewportBounds[0].y);

			/* Camera Run Time
			auto cameraEntity = d_ActiveScene->GetPrimaryCameraEntity();
			const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			const glm::mat4& cameraProjection = camera.GetProjection();
			glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());*/

			// Editor camera
			const glm::mat4& cameraProjection = d_EditorCamera.GetProjection();
			glm::mat4 cameraView = d_EditorCamera.GetViewMatrix();

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (d_GizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)d_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		d_CameraController.OnEvent(e);
		d_EditorCamera.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(DD_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(DD_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode())
		{
		case Key::N:
		{
			if (control)
				NewScene();
			break;
		}
		case Key::O:
		{
			if (control)
				OpenScene();
			break;
		}
		case Key::S:
		{
			if (control && shift)
				SaveSceneAs();
			break;
		}
		// Gizmos
		case Key::Q:
		{
			if (!ImGuizmo::IsUsing())
				d_GizmoType = -1;
			break;
		}
		case Key::W:
		{
			if (!ImGuizmo::IsUsing())
				d_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		}
		case Key::E:
		{
			if (!ImGuizmo::IsUsing())
				d_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		}
		case Key::R:
		{
			if (!ImGuizmo::IsUsing())
				d_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			//mouse picking, requirments to be able to select an entity in the scene pannel
			if (d_ViewportFocused && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
				d_SceneHierarchyPanel.SetSelectedEntity(d_HoveredEntity);
		}
		return false;
	}

	void EditorLayer::NewScene()
	{
		d_ActiveScene = CreateRef<Scene>();
		d_ActiveScene->OnViewportResize((UINT)d_ViewportSize.x, (UINT)d_ViewportSize.y);
		d_SceneHierarchyPanel.SetContext(d_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Dooda Scene (*.dooda)\0*.dooda\0");
		if (!filepath.empty())
			OpenScene(filepath);
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		d_ActiveScene = CreateRef<Scene>();
		d_ActiveScene->OnViewportResize((UINT)d_ViewportSize.x, (UINT)d_ViewportSize.y);
		d_SceneHierarchyPanel.SetContext(d_ActiveScene);

		SceneSerialiser serializer(d_ActiveScene);
		serializer.Deserialise(path.string());
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Dooda Scene (*.dooda)\0*.dooda\0");
		if (!filepath.empty())
		{
			//Ensure it has the right file type
			if (filepath.find_last_of(".") == filepath.npos)
				filepath.append(".dooda");

			SceneSerialiser serialiser(d_ActiveScene);
			serialiser.Serialise(filepath);
		}
	}

}
