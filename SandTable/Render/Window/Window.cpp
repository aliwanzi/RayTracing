#include "Window.h"

namespace SandTable
{
	namespace
	{
		void OnDebug(GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, GLvoid* userParam)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_MEDIUM:       LOG_DEV_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          LOG_DEVE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_DEV_INFO(message); return;
			}
		}

		bool IsExtensionSupported(const std::string& sExtersionName)
		{
			GLint numExtensions;
			glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

			for (int i = 0; i < numExtensions; i++)
			{
				if (std::string((char const*)glGetStringi(GL_EXTENSIONS, i)) == sExtersionName)
				{
					return true;
				}
			}
			return false;
		}
	}

	Window::Window(std::shared_ptr<WindowInfo> spWindowInfo): 
		m_pGLFWWindow(nullptr)
	{
		Init(spWindowInfo);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_pGLFWWindow);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_pGLFWWindow);
	}

	int Window::GetWindowWidth() const
	{
		return m_windowCallBack.WindowWidth;
	}

	int Window::GetWindowHeight() const
	{
		return m_windowCallBack.WindowHeight;
	}

	void Window::SetEventCallback(const EventCallback& callback)
	{
		m_windowCallBack.EventCallback = callback;
		glfwSetWindowUserPointer(m_pGLFWWindow, &m_windowCallBack);
	}

	GLFWwindow* Window::GetGLFWWindow()
	{
		return m_pGLFWWindow;
	}

	void Window::Init(std::shared_ptr<WindowInfo> spWindowInfo)
	{
		LOG_DEV_INFO("Creating window {0} ({1}, {2})", spWindowInfo->WindowTitle, spWindowInfo->WindowWidth, spWindowInfo->WindowHeight);
		if (!glfwInit())
		{
			LOG_DEV_ERROR("Failed to initialize GLFW\n");
			return;
		}
		m_windowCallBack.WindowWidth = spWindowInfo->WindowWidth;
		m_windowCallBack.WindowHeight = spWindowInfo->WindowHeight;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, spWindowInfo->MajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, spWindowInfo->MinorVersion);

		if (spWindowInfo->UnionFlags.Debug)
		{
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		}

		if (spWindowInfo->UnionFlags.Robust)
		{
			glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
		}

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, spWindowInfo->Samples);
		glfwWindowHint(GLFW_STEREO, spWindowInfo->UnionFlags.Stereo ? GL_TRUE : GL_FALSE);

		m_pGLFWWindow = glfwCreateWindow(spWindowInfo->WindowWidth,
			spWindowInfo->WindowHeight, spWindowInfo->WindowTitle.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_pGLFWWindow);

		 //Set GLFW callbacks
		glfwSetWindowSizeCallback(m_pGLFWWindow, [](GLFWwindow* window, int width, int height)
			{
				auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);
				pWindowCallBack.WindowWidth = width;
				pWindowCallBack.WindowHeight = height;

				WindowResizeEvent event(width, height);
				pWindowCallBack.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_pGLFWWindow, [](GLFWwindow* window)
			{
				auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				pWindowCallBack.EventCallback(event);
			});

		glfwSetKeyCallback(m_pGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);
				KeyPressEvent event(key);
				pWindowCallBack.EventCallback(event);
			});

		glfwSetScrollCallback(m_pGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
				pWindowCallBack.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_pGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);

				MouseMoveEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
				pWindowCallBack.EventCallback(event);
			});

		if (!spWindowInfo->UnionFlags.Cursor)
		{
			glfwSetInputMode(m_pGLFWWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		gl3wInit();
		LOG_DEV_INFO("OpenGL Info:");
		LOG_DEV_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LOG_DEV_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LOG_DEV_INFO("  Version: {0}", glGetString(GL_VERSION));

		if (spWindowInfo->UnionFlags.Debug)
		{
			if (gl3wIsSupported(4, 3))
			{
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
				glDebugMessageCallback((GLDEBUGPROC)OnDebug, this);
			}
			else if (IsExtensionSupported("GL_ARB_debug_output"))
			{
				glDebugMessageCallbackARB((GLDEBUGPROC)OnDebug, this);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			}
		}
	}
}