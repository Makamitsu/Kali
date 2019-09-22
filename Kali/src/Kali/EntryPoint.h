#pragma once

#ifdef KL_PLATFORM_WINDOWS

#ifndef KL_BUILD_DLL
extern Kali::Application* Kali::CreateApplication();
#endif

int main(int argc, char** argv)
{
	Kali::Log::Init();

	auto app = Kali::CreateApplication();
	app->run();
	delete app;
}

#else
	#error KALI is window only
#endif // KL_PLATFORM_WINDOWS
