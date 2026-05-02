#pragma once
#include <bgfx/bgfx.h>

namespace Vaelith
{
    enum class RenderView : uint16_t
    {
        Shadow = 0,
        Main = 1,
        PostProcess = 2,

        UI = 255
    };

	class RenderCommand
	{
	public:
        static void Init();

        static void SetViewport(RenderView viewID = RenderView::Main, uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0);

        static void Clear(RenderView viewID = RenderView::Main, uint16_t flags = BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, uint32_t rgba = 0x303030ff);

        static void Submit(RenderView viewID = RenderView::Main, bgfx::ProgramHandle program = BGFX_INVALID_HANDLE);
	};
}