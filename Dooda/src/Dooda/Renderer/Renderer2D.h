#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Dooda {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::string& textureKey, float tilingFactor = 1.0f, const glm::vec4& tintColour = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::string& textureKey, float tilingFactor = 1.0f, const glm::vec4& tintColour = glm::vec4(1.0f));
	
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotationDeg, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotationDeg, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotationDeg, const std::string& textureKey, float tilingFactor = 1.0f, const glm::vec4& tintColour = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotationDeg, const std::string& textureKey, float tilingFactor = 1.0f, const glm::vec4& tintColour = glm::vec4(1.0f));
	};

}
