#include "pch.h"
#include "Application.h"
#include "Config.h"
#include "Game.h"
#include "Graphics.h"
#include "ModelManager.h"
#include "TextureManager.h"


Application::Application() :
    m_hWnd(0),
	m_client_size({0})
{
}


Application::~Application()
{
}


void Application::CreateAppWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register window class
	WNDCLASSEX wcex;
	wcex.cbSize         = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WinProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, L"IDI_ICON");
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName   = nullptr;
	wcex.lpszClassName  = L"NeuralAntsWindowClass";
	wcex.hIconSm        = LoadIcon(wcex.hInstance, L"IDI_ICON");

	if(!RegisterClassEx(&wcex))
		throw std::exception();

	// Create window
	auto size = Config::Instance().GetDefaultWindowSize();
	auto fullscreen = Config::Instance().GetFullscreen();

	RECT rc;
	rc.top    = 0;
	rc.left   = 0;
	rc.right  = size.cx;
	rc.bottom = size.cy;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	if(fullscreen)
	{
		dwStyle  = WS_POPUP;
		nCmdShow = SW_SHOWMAXIMIZED;
	}
	
	m_hWnd = CreateWindowEx(0, L"NeuralAntsWindowClass", L"NeuralAnts", dwStyle,
		            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		            nullptr);

	if(!m_hWnd)
		throw std::exception();

	//ShowWindow(m_hWnd, nCmdShow);

	GetClientRect(m_hWnd, &rc);
	m_client_size.cx = rc.right - rc.left;
	m_client_size.cy = rc.bottom - rc.top;

}

// Message handlers
void Application::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Application::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Application::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Application::OnResuming()
{
	Game::Instance().ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Application::OnWindowSizeChanged(int width, int height)
{
	Graphics::Instance().Resize(width, height);
}

int Application::Run()
{
    ShowWindow(m_hWnd, SW_SHOW);
	
	// Main message loop
	MSG msg = { 0 };
	while(WM_QUIT != msg.message)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Game::Instance().DoFrame();
		}
	}

	return((int)msg.wParam);
}

void Application::Quit()
{
	PostQuitMessage(0);
}

void Application::Shutdown()
{
	/* Shutdown the services */
	Game::Instance().Shutdown();
	TextureManager::Instance().Shutdown();
	ModelManager::Instance().Shutdown();
	Graphics::Instance().Shutdown();
}

void Application::Startup()
{
	/* Start the services */
	Graphics::Instance().Startup();
	TextureManager::Instance().Startup();
	ModelManager::Instance().Startup();
	Game::Instance().Startup();
}

// Windows procedure
LRESULT CALLBACK Application::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static bool s_in_sizemove = false;
	static bool s_in_suspend = false;
	static bool s_minimized = false;
	static bool s_fullscreen = false;
	// TODO: Set s_fullscreen to true if defaulting to fullscreen.

	auto &app = Application::Instance();

	switch(message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		if(wParam == SIZE_MINIMIZED)
		{
			if(!s_minimized)
			{
				s_minimized = true;
				if(!s_in_suspend)
					app.OnSuspending();
				s_in_suspend = true;
			}
		}
		else if(s_minimized)
		{
			s_minimized = false;
			if(s_in_suspend)
				app.OnResuming();
			s_in_suspend = false;
		}
		else if(!s_in_sizemove)
		{
			app.OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
		}
		break;

	case WM_ENTERSIZEMOVE:
		s_in_sizemove = true;
		break;

	case WM_EXITSIZEMOVE:
		s_in_sizemove = false;
		RECT rc;
		GetClientRect(hWnd, &rc);
		app.OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
		break;

	case WM_GETMINMAXINFO:
	{
		auto info = reinterpret_cast<MINMAXINFO*>(lParam);
		info->ptMinTrackSize.x = 320;
		info->ptMinTrackSize.y = 200;
	}
	break;

	case WM_ACTIVATEAPP:
		if(wParam)
		{
			app.OnActivated();
		}
		else
		{
			app.OnDeactivated();
		}
		break;

	case WM_POWERBROADCAST:
		switch(wParam)
		{
		case PBT_APMQUERYSUSPEND:
			if(!s_in_suspend)
				app.OnSuspending();
			s_in_suspend = true;
			return TRUE;

		case PBT_APMRESUMESUSPEND:
			if(!s_minimized)
			{
				if(s_in_suspend)
					app.OnResuming();
				s_in_suspend = false;
			}
			return TRUE;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SYSKEYDOWN:
		if(wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// Implements the classic ALT+ENTER fullscreen toggle
			if(s_fullscreen)
			{
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

				auto size = Config::Instance().GetDefaultWindowSize();

				ShowWindow(hWnd, SW_SHOWNORMAL);

				SetWindowPos(hWnd, HWND_TOP, 0, 0, static_cast<int>(size.cx), static_cast<int>(size.cy), SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			else
			{
				SetWindowLongPtr(hWnd, GWL_STYLE, 0);
				SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

				SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

				ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			}

			s_fullscreen = !s_fullscreen;
		}
		break;

	case WM_MENUCHAR:
		// A menu is active and the user presses a key that does not correspond
		// to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
		return MAKELRESULT(0, MNC_CLOSE);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}