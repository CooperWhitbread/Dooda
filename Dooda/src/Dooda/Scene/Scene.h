#pragma once

#include "entt.hpp"
#include "Dooda/Core/Timestep.h"
#include "Dooda/Renderer/EditorCamera.h"

namespace Dooda {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRunTime(Timestep ts);
		void OnViewportResize(UINT width, UINT height);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);

		Entity GetPrimaryCameraEntity();//TODO remove from this class

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry d_Registry;
		UINT d_ViewportWidth = 0, d_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerialiser;
		friend class SceneHierarchyPanel;
	};
}
