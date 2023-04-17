#pragma once

#include "Dooda/Events/Event.h"

#include <sstream>

namespace Dooda 
{

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Dooda Engine", uint32_t width = 2560, uint32_t height = 1440)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

	public: //Getters
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual bool GetVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

	public: //Setters
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;

	public: //Static Functions
		static Scope<Window> SD_Create(const WindowProps& props = WindowProps());
	};
}
