#include "Application/Application.h"
#include "Examples/RenderLayer.h"

int main()
{
	SandTable::Application::CreateApplication("SandTable",1080,1080);

	auto spApplication = SandTable::Application::GetApplication();

	auto spRenderLayer = std::make_shared<SandTable::RenderLayer>();
	spApplication->PushLayer(spRenderLayer);

	spApplication->Run();
}