#include <Dooda.h>
#include <Dooda/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Dooda 
{
	class Adood : public Application
	{
	public:
		Adood(ApplicationCommandLineArgs args)
			: Application("Adood", args)
		{
			PushLayer(new EditorLayer());
		}

		~Adood()
		{

		}
	};

	Application* S_CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Adood(args);
	}
}
