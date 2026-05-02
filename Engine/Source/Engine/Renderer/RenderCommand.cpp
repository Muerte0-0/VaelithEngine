#include "vltpch.h"
#include "RenderCommand.h"

namespace Vaelith
{
	void RenderCommand::Init()
	{
		uint16_t order[] = {
			SHADOWPASS_VIEW_ID,
			MAINPASS_VIEW_ID,
			POSTPROCESS_VIEW_ID,
			UIPASS_VIEW_ID
		};

		bgfx::setViewOrder(0, 4, order);
	}

	void RenderCommand::SetViewport(uint16_t viewID, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
	{
		bgfx::setViewRect(viewID, x, y, width, height);
	}

	void RenderCommand::Clear(uint16_t viewID, uint16_t flags, uint32_t rgba)
	{
		bgfx::setViewClear(viewID, flags, rgba);
	}

	void RenderCommand::Submit(uint16_t viewID, bgfx::ProgramHandle program)
	{
		bgfx::submit(viewID, program);
	}
}