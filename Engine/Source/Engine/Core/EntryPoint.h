#pragma once
#include "Application.h"

extern Vaelith::Application* Vaelith::CreateApplication(int argc, char** argv);

inline bool g_ApplicationRunning = true;

inline int Main(int argc, char** argv)
{
	while (g_ApplicationRunning)
	{

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