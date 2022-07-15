#include <Dooda.h>
#include <Dooda/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Dooda 
{
	class Adood : public Application
	{
	public:
		Adood(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* S_CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Adood";
		spec.CommandLineArgs = args;

		return new Adood(spec);
	}
}
