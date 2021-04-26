#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Core/KeyCodes.h"
#include "Dooda/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Dooda {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}