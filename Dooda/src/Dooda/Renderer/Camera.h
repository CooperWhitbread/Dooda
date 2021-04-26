#pragma once

#include <glm/glm.hpp>

namespace Dooda {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: d_Projection(projection) {}

		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return d_Projection; }
	protected:
		glm::mat4 d_Projection = glm::mat4(1.0f);
	};
}
