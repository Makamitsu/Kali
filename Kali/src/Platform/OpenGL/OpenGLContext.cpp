#include "klpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace  Kali
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_windowHandle(windowHandle)
	{
		KL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		KL_CORE_ASSERT(status, "Failed to initialize Glad!");

		KL_CORE_INFO("OpenGL Info");
		KL_CORE_INFO("    - RENDERER {0}", glGetString(GL_RENDERER));
		KL_CORE_INFO("    - VERSION {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}
