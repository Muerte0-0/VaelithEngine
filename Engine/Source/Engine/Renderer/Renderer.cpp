#include "vltpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Vaelith
{
	void Renderer::Init(const RendererConfig& config)
	{
		bgfx::Init init{};

		init.type = bgfx::RendererType::Vulkan;
		init.platformData.nwh = config.NativeWindowHandle;
		init.platformData.ndt = nullptr;

		init.resolution.width = config.Width;
		init.resolution.height = config.Height;
		init.resolution.reset = config.VSync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE;

#ifdef DEBUG
		init.debug = true;
		init.profile = true;
#endif

		if (!bgfx::init(init))
		{
			LOG(LogLevel::Error, "bgfx init failed!\n");
			return;
		}

		bgfx::setDebug(BGFX_DEBUG_TEXT);
		RenderCommand::Clear(MAINPASS_VIEW_ID, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff);

		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{}

	void Renderer::BeginFrame()
	{
		RenderCommand::Clear(MAINPASS_VIEW_ID, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff);
		RenderCommand::Clear(UIPASS_VIEW_ID,   BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00000000);
		bgfx::touch(0);
	}

	void Renderer::EndFrame()
	{
		bgfx::frame();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0)
			return;

		bgfx::reset(width, height, BGFX_RESET_VSYNC);

		// Update all forward-allocated view rects to the new dimensions
		RenderCommand::SetViewport(SHADOWPASS_VIEW_ID,     0, 0, width, height);
		RenderCommand::SetViewport(MAINPASS_VIEW_ID,       0, 0, width, height);
		RenderCommand::SetViewport(POSTPROCESS_VIEW_ID,    0, 0, width, height);
		RenderCommand::SetViewport(UIPASS_VIEW_ID,         0, 0, width, height);
	}
}