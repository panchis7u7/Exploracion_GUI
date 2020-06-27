#include <iostream>
#include <Windows.h>
#include <WinUser.h>

static LRESULT CALLBACK windowEvent(HWND, UINT, WPARAM, LPARAM);
#if defined(UNICODE) || defined(_UNICODE)
	#define nombre(s) L##s
#else
	#define nombre(s) s
#endif

int main() {

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
	bool fullscreen = false	;
	HWND hwnd = nullptr;
	LONG* vWindowsSize = new LONG[2]{ 100, 100 };

	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
	wc.lpfnWndProc = windowEvent;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = nombre("Hola.");
	RegisterClass(&wc); //->https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa
	
	//Definir amueblado de la ventana.
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;								//Estilos -> https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
	DWORD dwStyle = WS_BORDER | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_THICKFRAME;	//Estilos -> https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
																						//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa

	if (fullscreen) {
		dwExStyle = 0;
		dwStyle = WS_VISIBLE | WS_POPUP;
		HMONITOR hmon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
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

	hwnd = CreateWindowEx(dwExStyle, nombre("Prueba."), nombre(""), dwStyle, 100, 100, width, height, NULL, NULL, GetModuleHandle(nullptr), NULL);
	if (hwnd == NULL)
		return 0;
	ShowWindow(hwnd, 5); //Params -> https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
	return 0;
}

static LRESULT CALLBACK windowEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}