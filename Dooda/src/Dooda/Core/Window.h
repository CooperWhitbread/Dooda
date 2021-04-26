#pragma once

#include <sstream>

#include "Dooda/Events/Event.h"

namespace Dooda 
{

	struct WindowProps
	{
		std::string Title;
		UINT Width;
		UINT Height;

		WindowProps(const std::string& title = "Dooda Engine", UINT width = 2560, UINT height = 1440)
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
		virtual UINT GetWidth() const = 0;
		virtual UINT GetHeight() const = 0;

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