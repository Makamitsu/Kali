#include "klpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "glad/glad.h"

namespace Kali
{

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::None:
			KL_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		KL_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}

}
