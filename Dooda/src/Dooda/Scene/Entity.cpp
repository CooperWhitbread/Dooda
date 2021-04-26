#include "Ddpch.h"
#include "Entity.h"

namespace Dooda {

	Entity::Entity(entt::entity handle, Scene* scene)
		: d_EntityHandle(handle), d_Scene(scene)
	{
	}

}
