#include "klpch.h"
#include "OpenGLShader.h"

#include "Kali/Core.h"

namespace Kali
{

	bool checkLink(GLuint program)
	{
		int isCompiled = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> infoLog(length);
			glGetProgramInfoLog(program, length, &length, &infoLog[0]);
			glDeleteProgram(program);

			KL_CORE_ERROR("GLSL ERROR: Program failed to link", infoLog.data());
			KL_CORE_ASSERT(false, "GLSL Program link failure!")

			return false;
		}
		return true;
	}

	bool checkCompilation(GLuint shader)
	{
		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(shader, length, &length, &infoLog[0]);
			glDeleteShader(shader);

			KL_CORE_ERROR("GLSL ERROR: \n{0}", infoLog.data());
			KL_CORE_ASSERT(false, "Shader compilation failure!")

			return false;
		}
		return true;
	}


	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		auto vertexSrc = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vertexSrc, 0);
		glCompileShader(vertexShader);

#ifdef KL_DEBUG		
		if (!checkCompilation(vertexShader)) return;
#endif

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		auto fragmentSrc = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSrc, 0);
		glCompileShader(fragmentShader);

#ifdef KL_DEBUG		
		if (!checkCompilation(fragmentShader)) return;
#endif

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		
		glLinkProgram(m_RendererID);

#ifdef KL_DEBUG		
		if (!checkLink(m_RendererID)) return;
#endif
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}


}
