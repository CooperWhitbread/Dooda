#pragma once

#include "Dooda/Core/Core.h"

#ifdef DD_PLATFORM_WINDOWS

extern Dooda::Application* Dooda::S_CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Dooda::Log::Init();

	DD_PROFILE_BEGIN_SESSION("Startup", "DoodaProfile-Startup.json");
	auto app = Dooda::S_CreateApplication({ argc, argv });
	DD_PROFILE_END_SESSION();

	DD_PROFILE_BEGIN_SESSION("Runtime", "DoodaProfile-Runtime.json");
	app->Run();
	DD_PROFILE_END_SESSION();

	DD_PROFILE_BEGIN_SESSION("Shutdown", "DoodaProfile-Shutdown.json");
	delete app;
	DD_PROFILE_END_SESSION();
}

#endif
