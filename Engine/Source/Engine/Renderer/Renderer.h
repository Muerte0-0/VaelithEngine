#pragma once

namespace Vaelith
{
    struct RendererConfig
    {
        void* NativeWindowHandle;

        uint32_t Width;
        uint32_t Height;

        bool VSync = true;
    };

	class Renderer
	{
    public:
        static void Init(const RendererConfig& config);
        static void Shutdown();

        static void BeginFrame();
        static void EndFrame();

        static void OnWindowResize(uint32_t width, uint32_t height);

        //static RendererStats GetStats();
	};
}