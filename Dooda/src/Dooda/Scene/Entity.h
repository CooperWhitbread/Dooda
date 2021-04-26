#pragma once

#include "Scene.h"

#include "entt.hpp"

namespace Dooda {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			DD_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return d_Scene->d_Registry.emplace<T>(d_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			DD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return d_Scene->d_Registry.get<T>(d_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return d_Scene->d_Registry.all_of<T>(d_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			DD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			d_Scene->d_Registry.remove<T>(d_EntityHandle);
		}

		operator bool() const { return d_EntityHandle != entt::null; }
	private:
		entt::entity d_EntityHandle{ entt::null };
		Scene* d_Scene = nullptr;
	};

}
