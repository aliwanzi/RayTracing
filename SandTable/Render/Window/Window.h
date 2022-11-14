#pragma once
#include <functional>

#include "./../../Core/Common.h"
#include "./../../Event/MouseEvent.h"
#include "./../../Event/KeyEvent.h"
#include "./../../Event/RenderEvent.h"

namespace SandTable 
{
	struct WindowInfo
	{
		std::string WindowTitle;
		int WindowWidth;
		int WindowHeight;
		int MajorVersion;
		int MinorVersion;
		int Samples;
		union
		{
			struct
			{
				unsigned int    Fullscreen : 1;
				unsigned int    Vsync : 1;
				unsigned int    Cursor : 1;
				unsigned int    Stereo : 1;
				unsigned int    Debug : 1;
				unsigned int    Robust : 1;
			};
			unsigned int        All;
		} UnionFlags;

		WindowInfo(const std::string& sTitle = "SandTable", int iWidth = 1920, int iHeight = 1080, int Samples = 0)
			: WindowTitle(sTitle), 
			WindowWidth(iWidth), 
			WindowHeight(iHeight),
			MajorVersion(4),
			MinorVersion(3), 
			Samples(Samples)
		{
		}
	};

	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;
		Window(std::shared_ptr<WindowInfo> spWindowInfo);
		~Window();

		void Update();

		int GetWindowWidth() const;
		int GetWindowHeight() const;

		void SetEventCallback(const EventCallback& windowCallback);

		GLFWwindow* GetGLFWWindow();
	private:
		void Init(std::shared_ptr<WindowInfo> spWindowInfo);

	private:
		struct WindowCallBack
		{
			int	WindowWidth;
			int WindowHeight;
			EventCallback EventCallback;
		};

		WindowCallBack m_windowCallBack;

		GLFWwindow* m_pGLFWWindow;
	};

}
