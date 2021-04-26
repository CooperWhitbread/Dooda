#include "Ddpch.h"
#include "Scene.h"

#include "Component.h"
#include "Entity.h"
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

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { d_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{// Update scripts
		{
			d_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.InstantiateFunction();
						nsc.Instance->d_Entity = Entity{ entity, this };

						if (nsc.OnCreateFunction)
							nsc.OnCreateFunction(nsc.Instance);
					}

					if (nsc.OnUpdateFunction)
						nsc.OnUpdateFunction(nsc.Instance, ts);
				});
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto group = d_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = d_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(UINT width, UINT height)
	{
		d_ViewportWidth = width;
		d_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = d_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}

	}
}