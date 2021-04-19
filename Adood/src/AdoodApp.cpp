#include "Dooda.h"
#include <Dooda/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Dooda {
	class Adood : public Application
	{
	public:
		Adood()
			: Application("Adood")
		{
			PushLayer(new EditorLayer());
		}

		~Adood()
		{

		}
	};

	Application* S_CreateApplication()
	{
		return new Adood;
	}
}