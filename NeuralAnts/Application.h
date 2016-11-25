#pragma once
class Application : public Singleton<Application>
{
	friend class Singleton < Application > ;
public:
	Application();
	~Application();

	HWND GetWindowHandle() const { return(m_hWnd); }
	void CreateAppWindow(HINSTANCE hInstance, int nCmdShow);
	void Quit();
	void Startup();
	void Shutdown();
	int Run();

private:
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	HWND                   m_hWnd;
	SIZE                   m_client_size;

};

