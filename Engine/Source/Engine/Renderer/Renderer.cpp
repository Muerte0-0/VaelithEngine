#include "vltpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Vaelith
{
    void Renderer::Init(const RendererConfig& config)
    {
        bgfx::Init init;

        init.type = bgfx::RendererType::Vulkan;
        init.platformData.nwh = config.NativeWindowHandle;

        init.resolution.width = config.Width;
        init.resolution.height = config.Height;
        init.resolution.reset = config.VSync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE;

        bgfx::init(init);

        bgfx::setDebug(BGFX_DEBUG_TEXT);
        RenderCommand::Clear(RenderView::Main, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff);

		RenderCommand::Init();
    }

    void Renderer::Shutdown()
    {}

    void Renderer::BeginFrame()
    {
        bgfx::touch(0);
    }

    void Renderer::EndFrame()
    {
		bgfx::frame();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
		RenderCommand::SetViewport(RenderView::Main, 0, 0, width, height);
    }
}