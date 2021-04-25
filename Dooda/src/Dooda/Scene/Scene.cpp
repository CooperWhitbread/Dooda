#include "Ddpch.h"
#include "Scene.h"

#include "Component.h"
#include "Dooda/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Dooda {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{
	#if ENTT_EXAMPLE_CODE
			entt::entity entity = d_Registry.create();
			d_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

			d_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


			if (d_Registry.has<TransformComponent>(entity))
				TransformComponent& transform = d_Registry.get<TransformComponent>(entity);


			auto view = d_Registry.view<TransformComponent>();
			for (auto entity : view)
			{
				TransformComponent& transform = view.get<TransformComponent>(entity);
			}

			auto group = d_Registry.group<TransformComponent>(entt::get<MeshComponent>);
			for (auto entity : group)
			{
				auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
			}
	#endif
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return d_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = d_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}