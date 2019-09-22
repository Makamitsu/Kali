#pragma once
#include "Kali/Renderer/Shader.h"

#include "glad/glad.h"

namespace Kali
{
	

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		GLuint m_RendererID;
	};

}
