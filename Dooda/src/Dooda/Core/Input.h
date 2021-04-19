#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Core/KeyCodes.h"
#include "Dooda/Core/MouseCodes.h"

namespace Dooda {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}