#pragma once

#include "Dooda/Core/Core.h"
#include "Dooda/Core/KeyCodes.h"
#include "Dooda/Core/MouseCodes.h"

namespace Dooda {

	class Input
	{
	protected:
		Input() = default;
		//~Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(KeyCode key) { return sd_Instance->IsKeyPressedImpl(key); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return sd_Instance->IsMouseButtonPressedImpl(button); }

		static Scope<Input> Create();

	public: //Getters
		inline static std::pair<float, float> GetMousePosition() { return sd_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return sd_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return sd_Instance->GetMouseYImpl(); }

	protected: //Private Functions
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private: //Variables
		static Scope<Input> sd_Instance;
	};

}