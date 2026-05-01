#pragma once
#include "Engine/Core/Application.h"
#include "Engine/Debugging/Log.h"

namespace Vaelith
{
	inline void InitializeCore(const ApplicationSpecification& applicationSpec)
	{
		Log::Init(applicationSpec.Name);
	}
	
	inline void ShutdownCore()
	{
		Log::Shutdown();
	}
}
