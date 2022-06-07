#pragma once

#include <Dooda.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Dooda/Renderer/EditorCamera.h"

namespace Dooda {

	class EditorLayer : public Dooda::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		OrthographicCameraController d_CameraController;

		Ref<VertexArray> d_SquareVA;
		Ref<Shader> d_FlatColorShader;
		Ref<Framebuffer> d_Framebuffer;
		glm::vec2 d_ViewportSize = glm::vec2(0.0f, 0.0f);

		glm::vec2 d_ViewportBounds[2];

		int d_GizmoType = -1;

		// Panels
		SceneHierarchyPanel d_SceneHierarchyPanel;

		Ref<Scene> d_ActiveScene;
		Entity d_SquareEntity;
		Entity d_CameraEntity;
		Entity d_SecondCamera;
		Entity d_HoveredEntity;

		bool d_PrimaryCamera = true;
		EditorCamera d_EditorCamera;

		Ref<Texture2D> d_CheckerboardTexture;
		bool d_ViewportFocused = false, d_ViewportHovered = false;

		glm::vec4 d_SquareColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
	};
}
