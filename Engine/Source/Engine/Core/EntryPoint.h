#pragma once
#include "Application.h"
#include "Core.h"

extern Vaelith::Application* Vaelith::CreateApplication(int argc, char** argv);

inline bool g_ApplicationRunning = true;

inline int Main(int argc, char** argv)
{
	while (g_ApplicationRunning)
	{
		Vaelith::Application* app = Vaelith::CreateApplication(argc, argv); // Create the Application Instance

		Vaelith::InitializeCore(app->GetApplicationSpecs());

		app->Initialize(); // Initialize Application
		app->Run(); // Run the Application Loop
		app->Shutdown(); // Shut-down Application

		delete app; // Clean up the Application instance

		Vaelith::ShutdownCore(); // Shut-down the Core systems of the Engine
	}

	return 0;
}

#if defined(DIST) && defined(PLATFORM_WINDOWS)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
{
	return Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Main(argc, argv);
}

#endif