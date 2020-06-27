#include <iostream>
#include <Windows.h>
#include <WinUser.h>

#if defined(UNICODE) || defined(_UNICODE)
	#define nombre(s) L##s
#else
	#define nombre(s) s
#endif

static LRESULT CALLBACK windowEvent(HWND, UINT, WPARAM, LPARAM);
bool broadcast();

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
int main(){
	/*typedef WNDCLASSW WNDCLASS; https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassw
	typedef struct tagWNDCLASSW {
		UINT      style;		class_styles -> https://docs.microsoft.com/en-us/windows/win32/winmsg/window-class-styles
		WNDPROC   lpfnWndProc;  windowProc CALLBACK f(x) -> https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633573(v=vs.85)
		int       cbClsExtra;
		int       cbWndExtra;
		HINSTANCE hInstance;
		HICON     hIcon;
		HCURSOR   hCursor;		parametros -> https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadcursora
		HBRUSH    hbrBackground;
		LPCWSTR   lpszMenuName;
		LPCWSTR   lpszClassName;
	} WNDCLASSW, * PWNDCLASSW, * NPWNDCLASSW, * LPWNDCLASSW;*/

	/*HICON LoadIconA(
		HINSTANCE hInstance, -> standard icon is loaded
		LPCSTR    lpIconName -> icon
	);*/
	bool fullscreen = false;
	HWND fullhwnd = NULL;
	LONG vWindowsSize[2] = { 700, 500  };

	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
	wc.lpfnWndProc = windowEvent;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = nullptr;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"MyWindowClass";
	RegisterClass(&wc); //->https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa
	
	//Definir amueblado de la ventana.
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			//Estilos -> https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
	DWORD dwStyle =  WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE | WS_CAPTION;			//Estilos -> https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
																						//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa

	if (fullscreen) {
		dwExStyle = 0;
		dwStyle = WS_VISIBLE | WS_POPUP;
		HMONITOR hmon = MonitorFromWindow(fullhwnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
		if (!GetMonitorInfo(hmon, &mi)) return 0;
		//vWindowsSize = { mi.rcMonitor.right, mi.rcMonitor.bottom};
		vWindowsSize[0] = mi.rcMonitor.right;
		vWindowsSize[1] = mi.rcMonitor.bottom;
	}

	RECT rWndRect = {0, 0, vWindowsSize[0], vWindowsSize[1]};
	AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
	int width = rWndRect.right - rWndRect.left;
	int height = rWndRect.bottom - rWndRect.top;

	HWND hwnd = CreateWindowEx(dwExStyle, L"MyWindowClass", L"Mi ventana.", dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, NULL, NULL);
	int x = GetLastError();
	if (hwnd == NULL)
		MessageBox(NULL, L"Error!", L"ERROR", MB_ICONWARNING);
	ShowWindow(hwnd, SW_SHOW); //Params -> https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
	UpdateWindow(hwnd);
	bool appRunning = true;
	while (appRunning) {
		broadcast();
	}
	return 0;
}

static LRESULT CALLBACK windowEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDc = BeginPaint(hwnd, &ps);
			FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_CREATE:
		{
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}

bool broadcast() {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}