#pragma once

#include "Dooda/Core/Window.h"
#include "Dooda/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Dooda
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

	public: //Getters
		inline unsigned int GetWidth() const override { return d_Data.Width; }
		inline unsigned int GetHeight() const override { return d_Data.Height; }

		bool GetVSync() const override;
		inline virtual void* GetNativeWindow() const { return d_Window; }

	public: //Setters
		inline void SetEventCallback(const EventCallbackFn& callback) override { d_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* d_Window;
		Scope<GraphicsContext> d_Context;

		struct WindowData
		{
			std::string Title = std::string("Defult");
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};

		WindowData d_Data;
	};
}