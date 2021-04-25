#pragma once

#include "entt.hpp"
#include "Dooda/Core/Timestep.h"

namespace Dooda {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return d_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry d_Registry;
	};
}
