#include <Dooda.h>
#include <Dooda/Core/EntryPoint.h>

#include "TestingLayer.h"

class Sandbox : public Dooda::Application
{
public:
	Sandbox(const Dooda::ApplicationSpecification& specification)
	: Dooda::Application(specification)
	{
		PushLayer(new TestingLayer());
	}
	~Sandbox()
	{
	}
};

Dooda::Application* Dooda::S_CreateApplication(Dooda::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Adood";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}
