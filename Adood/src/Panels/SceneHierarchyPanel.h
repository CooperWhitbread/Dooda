#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Scene/Scene.h"
#include "Dooda/Scene/Entity.h"

namespace Dooda {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return d_SelectionContext; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> d_Context;
		Entity d_SelectionContext;
	};

}
