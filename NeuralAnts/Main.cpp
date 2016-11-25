//
// Main.cpp
//

#include "pch.h"
#include "Application.h"
#include "Config.h"
#include "Game.h"

#define FAILURE         1

// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	using namespace DX;
	auto &app = Application::Instance();
	try
	{
		/* Verify we have hardware support */
		ThrowIfFailed(DirectX::XMVerifyCPUSupport());

		/* Initialize COM with multi-thread support */
		ThrowIfFailed(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

		/* Startup the Configuration */
		Config::Instance().Startup();

		/* Create the application window */
		app.CreateAppWindow(hInstance, nCmdShow);

		/* Start the simulation application */
		app.Startup();
	}
	catch(const std::exception& e )
	{
		return(FAILURE);
	}

	/* Run the simulation */
	auto return_code = 0;
	try
	{
		return_code = app.Run();
	}
	catch(const std::exception)
	{
		return_code = FAILURE;
	}
    
	/* Shutdown the simulation application */
	app.Shutdown();

	/* Uninitialize COM */
    CoUninitialize();

    return(return_code);
}