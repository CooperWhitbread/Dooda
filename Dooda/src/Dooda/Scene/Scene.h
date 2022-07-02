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

		void OnUpdateRunTime(Timestep ts);
		void OnViewportResize(UINT width, UINT height);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);

		void DuplicateEntity(Entity entity);

		Entity GetPrimaryCameraEntity();//TODO remove from this class

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry d_Registry;
		UINT d_ViewportWidth = 0, d_ViewportHeight = 0;

		b2World* d_PhysicsWorld = nullptr;

		friend class Entity;
		friend class SceneSerialiser;
		friend class SceneHierarchyPanel;
	};
}
