#include "Application.h"
#include "./../Render/Command/Render.h"
#include "./../Event/SystemDispatcher.h"

namespace SandTable 
{
	std::shared_ptr<Application> Application::m_spApplication;

	std::shared_ptr<Application>& Application::GetApplication()
	{
		return m_spApplication;
	}

	std::shared_ptr<Application>& Application::CreateApplication(const std::string& sApplicationName /*= "SandTabel"*/,
		int iWindowWidth /*= 1920*/, int iWindowHeight /*= 1080*/)
	{
		Logger::Init();

		auto spWindowInfo = std::make_shared<WindowInfo>();
		spWindowInfo->WindowWidth = iWindowWidth;
		spWindowInfo->WindowHeight = iWindowHeight;
		spWindowInfo->MajorVersion = 4;
		spWindowInfo->MinorVersion = 3;
		spWindowInfo->Samples = 0;
		spWindowInfo->UnionFlags.All = 0;
		spWindowInfo->UnionFlags.Cursor = 1;
		spWindowInfo->UnionFlags.Debug = 1;

		m_spApplication = std::shared_ptr<Application>(new Application());
		m_spApplication->Init(spWindowInfo);
		return m_spApplication;
	}

	Application::Application():
		m_bRunning(true),
		m_spWindow(nullptr),
		m_spImGuiLayer(nullptr)
	{

	}

	void Application::Init(std::shared_ptr<WindowInfo> spWindowInfo)
	{
		m_spWindow = std::make_shared<Window>(spWindowInfo);

		m_spWindow->SetEventCallback(BIND_EVENT(Application::ExecuteEvent));

		Render::Init();

		m_spImGuiLayer = std::make_shared<ImGuiLayer>();
		m_spImGuiLayer->Attach();
	}

	Application::~Application()
	{
		Render::Shutdown();
	}

	void Application::PushLayer(std::shared_ptr<Layer> spLayer)
	{
		m_vecLayers.push_back(spLayer);
		spLayer->Attach();
	}

	std::shared_ptr<Window> Application::GetWindow() const
	{
		return m_spWindow;
	}

	void Application::Run()
	{
		while (m_bRunning)
		{
			for (auto layer : m_vecLayers)
			{
				layer->Execute();
			}

			m_spImGuiLayer->Begin();
			for (auto layer : m_vecLayers)
			{
				layer->ExecuteImGui();
			}
			m_spImGuiLayer->End();

			m_spWindow->Update();
		}
		glfwTerminate();
	}

	void Application::Close()
	{
		m_bRunning = false;
	}

	void Application::ExecuteEvent(Event& e)
	{
		SystemDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::WindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::WindowResize));
		dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT(Application::KeyPress));

		for (auto iter = m_vecLayers.begin(); iter != m_vecLayers.end(); ++iter)
		{
			(*iter)->ExecuteEvent(e);
		}
	}

	bool Application::WindowClose(WindowCloseEvent& e)
	{
		m_bRunning = false;
		return true;
	}

	bool Application::WindowResize(WindowResizeEvent& e)
	{
		Render::WindowResize(e.GetWindowWidth(), e.GetWindowHeight());

		return true;
	}
	bool Application::KeyPress(KeyPressEvent& e)
	{
		if (GLFW_KEY_ESCAPE == e.GetKeyCode())
		{
			m_bRunning = false;
		}
		return false;
	}
}