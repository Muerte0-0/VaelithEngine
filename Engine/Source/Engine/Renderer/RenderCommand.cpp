#include "vltpch.h"
#include "RenderCommand.h"

namespace Vaelith
{
	void RenderCommand::Init()
	{
		uint16_t order[] = {
			(uint16_t) RenderView::Shadow,
			(uint16_t) RenderView::Main,
			(uint16_t) RenderView::PostProcess,
			(uint16_t) RenderView::UI
		};

		bgfx::setViewOrder(0, 4, order);
	}

	void RenderCommand::SetViewport(RenderView viewID, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
	{
		bgfx::setViewRect((uint16_t)viewID, x, y, width, height);
	}

	void RenderCommand::Clear(RenderView viewID, uint16_t flags, uint32_t rgba)
	{
		bgfx::setViewClear((uint16_t)viewID, flags, rgba);
	}

	void RenderCommand::Submit(RenderView viewID, bgfx::ProgramHandle program)
	{
		bgfx::submit((uint16_t)viewID, program);
	}
}