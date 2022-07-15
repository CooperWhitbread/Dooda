#pragma once

#include "entt.hpp"
#include "Dooda/Core/Timestep.h"
#include "Dooda/Core/UUID.h"
#include "Dooda/Renderer/EditorCamera.h"

class b2World;

namespace Dooda {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnSimulationStart();
		void OnSimulationStop();

		void OnUpdateRunTime(Timestep ts);
		void OnUpdateSimulation(Timestep ts, EditorCamera& camera);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);

		void OnViewportResize(UINT width, UINT height);

		void DuplicateEntity(Entity entity);

		Entity GetPrimaryCameraEntity();//TODO remove from this class
		template<typename... Components>
		auto GetAllEntitiesWith() { return d_Registry.view<Components...>(); }

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void OnPhysics2DStart();
		void OnPhysics2DStop();

		void RenderScene(EditorCamera& camera);

	private:
		entt::registry d_Registry;
		UINT d_ViewportWidth = 0, d_ViewportHeight = 0;

		b2World* d_PhysicsWorld = nullptr;

		friend class Entity;
		friend class SceneSerialiser;
		friend class SceneHierarchyPanel;
	};
}
