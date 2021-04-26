#pragma once

#include "Entity.h"

namespace Dooda {

	class ScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return d_Entity.GetComponent<T>();
		}
	private:
		Entity d_Entity;
		friend class Scene;
	};

}
