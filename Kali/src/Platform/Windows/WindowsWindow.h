#pragma once

#include "Kali/Window.h"
#include "Kali/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Kali {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const Kali::WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		[[nodiscard]] unsigned int GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override;

		[[nodiscard]] void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GLFWcursor* m_ImGuiMouseCursors[9] = { 0 };

		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}