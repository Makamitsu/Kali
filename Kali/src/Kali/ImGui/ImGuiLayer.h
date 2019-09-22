#pragma once

#include "Kali/Layer.h"

namespace Kali
{
	class KeyTypedEvent;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class WindowResizeEvent;
	class MouseScrolledEvent;
	class MouseMovedEvent;
	class MouseButtonReleasedEvent;
	class MouseButtonPressedEvent;

	class KALI_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;

	};


}
