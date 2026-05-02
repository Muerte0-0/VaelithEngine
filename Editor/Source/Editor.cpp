// -------- Entry Point -------- //
#include "Engine/Core/EntryPoint.h"
// ----------------------------- //

#include "EditorLayer.h"

namespace Vaelith
{

	class Editor : public Application
	{
	public:
		Editor()
		{
			PushLayer<EditorLayer>();
		}

		ApplicationSpecification GetApplicationSpecs() const override
		{
			ApplicationSpecification appSpec;
			appSpec.Name = "KairosEditor";
			//appSpec.Theme = Theme::Mocha;
			appSpec.ShaderSourcePath = "Editor/Resources/Shaders";
			appSpec.CompileShadersOnStartup = true;

			WindowSpecification windowSpec;
			windowSpec.Title = "Kairos Editor";
			windowSpec.Width = 1280;
			windowSpec.Height = 720;
			windowSpec.CustomTitleBar = false;
			windowSpec.LaunchMaximized = true;
			appSpec.WindowSpec = windowSpec;

			return appSpec;
		}
	};
}

Vaelith::Application* Vaelith::CreateApplication(int argc, char** argv)
{
	return new Vaelith::Editor();
}