#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Scene/Scene.h"

namespace Dooda 
{

	class SceneSerialiser
	{
	public:
		SceneSerialiser(const Ref<Scene>& scene);

		void Serialise(const std::string& filepath);
		void SerialiseRuntime(const std::string& filepath);

		bool Deserialise(const std::string& filepath);
		bool DeserialiseRuntime(const std::string& filepath);
	private:
		Ref<Scene> d_Scene;
	};

}
