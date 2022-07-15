#pragma once

#include <glm/glm.hpp>

namespace Dooda 
{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

	public: //Getters
		const glm::vec3& GetPosition() const { return d_Position; }
		float GetRotation() const { return d_Rotation; }

		const glm::mat4& GetProjectionMatrix() const { return d_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return d_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return d_ViewProjectionMatrix; }

	public: //Setters
		void SetPosition(const glm::vec3& position);
		void SetProjection(float left, float right, float bottom, float top);
		void SetRotation(const float rotation);

	private: //Private Functions
		void RecalculateViewMatrix();

	private: //Variables
		glm::mat4 d_ProjectionMatrix;
		glm::mat4 d_ViewMatrix;
		glm::mat4 d_ViewProjectionMatrix;

		glm::vec3 d_Position = glm::vec3( 0.0f, 0.0f, 0.0f );
		float d_Rotation = 0.0f;
	};

}
