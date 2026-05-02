#pragma once
#include <bgfx/bgfx.h>

namespace Vaelith
{
#define SHADOWPASS_VIEW_ID 0
#define MAINPASS_VIEW_ID 1
#define POSTPROCESS_VIEW_ID 2
#define UIPASS_VIEW_ID 255

	class RenderCommand
	{
	public:
        static void Init();

        static void SetViewport(uint16_t viewID = MAINPASS_VIEW_ID, uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0);

        static void Clear(uint16_t viewID = MAINPASS_VIEW_ID, uint16_t flags = BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, uint32_t rgba = 0x303030ff);

		static void Submit(uint16_t viewID = MAINPASS_VIEW_ID, bgfx::ProgramHandle program = BGFX_INVALID_HANDLE);
	};
}