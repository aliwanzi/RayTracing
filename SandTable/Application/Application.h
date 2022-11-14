#pragma once
#include "./../Core/Common.h"
#include "./../Render/Window/Window.h"
#include "./../Render/Layers/Layer.h"
#include "./../Render/Layers/ImGuiLayer.h"

namespace SandTable
{
	class Application
	{
	public:

		virtual ~Application();

		void Init(std::shared_ptr<WindowInfo> spWindowInfo);

		void ExecuteEvent(Event& e);

		void PushLayer(std::shared_ptr<Layer> spLayer);

		std::shared_ptr<Window> GetWindow()const;

		void Run();
		void Close();

		static std::shared_ptr<Application>& GetApplication();
		static std::shared_ptr<Application>& CreateApplication(const std::string& sApplicationName = "SandTabel",
			int iWindowWidth = 1920, int iWindowHeight = 1080);

	private:
		Application();
		Application(Application&) = delete;
		bool WindowClose(WindowCloseEvent& e);
		bool WindowResize(WindowResizeEvent& e);
		bool KeyPress(KeyPressEvent& e);

	private:
		bool m_bRunning;
		std::shared_ptr<Window> m_spWindow;

		std::shared_ptr<ImGuiLayer> m_spImGuiLayer;
		std::vector<std::shared_ptr<Layer>> m_vecLayers;

		static std::shared_ptr<Application> m_spApplication;
	};
}
