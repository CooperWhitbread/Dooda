#pragma once

namespace Dooda {

	class Input
	{
	protected:
		Input() = default;
		//~Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return sd_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return sd_Instance->IsMouseButtonPressedImpl(button); }

	public: //Getters
		inline static std::pair<float, float> GetMousePosition() { return sd_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return sd_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return sd_Instance->GetMouseYImpl(); }

	protected: //Private Functions
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private: //Variables
		static Scope<Input> sd_Instance;
	};

}