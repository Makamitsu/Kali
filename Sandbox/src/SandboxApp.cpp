#include <Kali.h>
#include "imgui.h"


class ExampleLayer : public Kali::Layer
{
public:
	ExampleLayer(): 
		Layer("Example")
	{
		
	}

	void OnUpdate() override
	{

	}

	void OnImGuiRender() override
	{
		//ImGui::Begin("SandBox ImGui");
		//ImGui::Text("Hello world!");
		//ImGui::End();
	}

	void OnEvent(Kali::Event& e) override
	{

	}
};

class Sandbox : public Kali::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() = default;
};


Kali::Application* Kali::CreateApplication()
{
	return new Sandbox();
}

