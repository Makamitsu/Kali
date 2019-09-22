#include "klpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Kali/LayerStack.h"

#include "glad/glad.h"

#include "Kali/Input.h"

namespace Kali {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		////////////////////////// DATA ///////////////////////////
		float vertices[7 * 3] = {
			/*position*/ -0.5f, -0.5f, 0.0f, /*color*/  1.0f,  0.0f, 0.0f, 1.0f,
			/*position*/  0.5f, -0.5f, 0.0f, /*color*/  0.0f,  1.0f, 0.0f, 1.0f,
			/*position*/  0.0f,  0.5f, 0.0f, /*color*/  0.0f,  0.0f, 1.0f, 1.0f
		};

		float vertices2[3 * 4] = {
			/*position*/ -0.8f, -0.8f, 0.0f,
			/*position*/  0.8f, -0.8f, 0.0f,
			/*position*/  -0.8f, 0.8f, 0.0f,
			/*position*/  0.8f,  0.8f, 0.0f,
		};

		uint32_t indices[3] = {
			0, 1, 2
		};
		
		uint32_t indices2[6] = {
			0, 1, 2,
			1, 2, 3
		};

		std::string vertexSource = R"(
		#version 330 core
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec4 v_Color;
		void main(){
			v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);
		}
		)";
		std::string fragmentSource = R"(
		#version 330 core
		layout(location = 0) out vec4 color;
		in vec4 v_Color;
		void main(){
			color = v_Color;
		}
		)";


		std::string vertexSourceBlue = R"(
		#version 330 core
		layout(location = 0) in vec3 a_Position;
		void main(){
			gl_Position = vec4(a_Position, 1.0);
		}
		)";
		std::string fragmentSourceBlue = R"(
		#version 330 core
		layout(location = 0) out vec4 color;
		void main(){
			color = vec4(1.0, 0.2, 0.6, 1.0);
		}
		)";
		////////////////////////// DATA ///////////////////////////

		m_SquareVA.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> squareVB;
		std::shared_ptr<IndexBuffer> squareIB;
		squareVB.reset(VertexBuffer::Create(vertices2, sizeof(vertices2)));
		squareIB.reset(IndexBuffer::Create(indices2, sizeof(indices2)));
		m_BlueShader.reset(Shader::Create(vertexSourceBlue, fragmentSourceBlue));
		squareVB->SetLayout( {{ ShaderDataType::Float3, "a_Position" }} );
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);


		m_VertexArray.reset(VertexArray::Create());

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices) ));
		BufferLayout layout = { {ShaderDataType::Float3, "a_Position" },
								{ShaderDataType::Float4, "a_Color" }, };
		
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader.reset(Shader::Create(vertexSource, fragmentSource));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() = default;

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher(e).Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		KL_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::run()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		while (m_Running)
		{

			glClear(GL_COLOR_BUFFER_BIT);


			m_BlueShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);



			for(Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}
