#include "EngineInterface.hxx"
#include "/sandbox/GAM300/GAM300Engine/Include/application.h"
#pragma comment (lib, "GAM300Engine.lib")


namespace ScriptAPI
{
	void EngineInterface::HelloWorld()
	{
		System::Console::WriteLine("Hello Managed World!");
		TDS::Application::HelloWorld();
	}
}