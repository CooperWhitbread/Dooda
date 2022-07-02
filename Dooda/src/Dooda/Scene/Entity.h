#pragma once

#include "Component.h"
#include "Scene.h"
#include "Dooda/Core/UUID.h"

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
			T& component = d_Scene->d_Registry.emplace<T>(d_EntityHandle, std::forward<Args>(args)...);
			d_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = d_Scene->d_Registry.emplace_or_replace<T>(d_EntityHandle, std::forward<Args>(args)...);
			d_Scene->OnComponentAdded<T>(*this, component);
			return component;
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
		operator UINT() const { return (UINT)d_EntityHandle; }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		bool operator==(const Entity& other) const
		{
			return d_EntityHandle == other.d_EntityHandle && d_Scene == other.d_Scene;
		}
		operator entt::entity() const { return d_EntityHandle; }
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity d_EntityHandle{ entt::null };
		Scene* d_Scene = nullptr;
	};

}
