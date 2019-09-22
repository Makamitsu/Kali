#pragma once

#include "Kali/Core.h"
#include "Kali/Events/Event.h"

namespace Kali
{
	
	class KALI_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}

		virtual void OnEvent(Event& e) {}

		const std::string& GetName() { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}
