#pragma once


namespace Kali
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};


	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_Renderer_api; }

	private:
		static RendererAPI s_Renderer_api;
		
	};

}