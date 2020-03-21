#include "Dooda.h"
#include <Dooda/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class SandBox : public Dooda::Application
{
public:
	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~SandBox()
	{
		
	}
};

Dooda::Application* Dooda::S_CreateApplication()
{
	return new SandBox;
}