#include <iostream>
#include <Windows.h>
#include <WinUser.h>

#if defined(UNICODE) || defined(_UNICODE)
	#define nombre(s) L##s
#else
	#define nombre(s) s
#endif

//ESTRUCTURA QUE IMPLEMENTA MANEJO DE VECTORES.
template <typename T>
struct VEC_2DTEMPLATE {
	T x;	//COMPONENTE X DEL VECTOR.
	T y;	//COMPONENTE Y DEL VECTOR.
	T Mag_Sqrt() { return sqrt(x * x + y * y); }		//MAGNITUD DEL VECTOR.
	T Mag() { return x * x + y * y; }		//MAGNITUD DEL VECTOR.
	T Dot(const VEC_2DTEMPLATE& vec) { return this->x * vec.x + this->y * vec.y; }	//PRODUCTO PUNTO ENTRE 2 VECTORES.
	T Cruz(const VEC_2DTEMPLATE& vec) { return this->x * vec.y - this->y * vec.x; }	//PRODUCTO CRUZ ENTRE 2 VECTORES.
	VEC_2DTEMPLATE() : x(0), y(0) {}	//LISTA DE INICIALIZACION DE MIEMBROS A 0.
	VEC_2DTEMPLATE(T _x, T _y) : x(_x), y(_y) {}		//LISTA DE INICIALIZACION DE MIEMBROS.
	VEC_2DTEMPLATE(const VEC_2DTEMPLATE& vec) : x(vec.x), y(vec.y) {}	//CONSTRUCTOR DE COPIA DE VECTORES.
	VEC_2DTEMPLATE(VEC_2DTEMPLATE&& vec) { x = std::move(vec.x); y = std::move(vec.y); }		//CONSTRUCTOR DE COPIA DE VECTORES.
	VEC_2DTEMPLATE Normalizar() { T norm = 1 / Mag_Sqrt(); return VEC_2DTEMPLATE(x * norm, y * norm); }	//NORMALIZAR UN VECTOR.
	VEC_2DTEMPLATE Perpendicular() { return VEC_2DTEMPLATE(-y, x); }	//OBTENER LA PERPPENDICULAR DE UN VECTOR.
	VEC_2DTEMPLATE operator +(const VEC_2DTEMPLATE& vec_derecha) const { return VEC_2DTEMPLATE(this->x + vec_derecha.x, this->y + vec_derecha.y); }	//OPERATOR DE ADICION DE VECTORES.
	VEC_2DTEMPLATE operator -(const VEC_2DTEMPLATE& vec_derecha) const { return VEC_2DTEMPLATE(this->x - vec_derecha.x, this->y - vec_derecha.y); }	//OPERATOR DE SUBSTRACCION DE VECTORES.
	VEC_2DTEMPLATE operator *(const VEC_2DTEMPLATE& vec_derecha) const { return VEC_2DTEMPLATE(this->x * vec_derecha.x, this->y * vec_derecha.x); }	//OPERATOR DE PRODUCTO DE VECTORES.
	VEC_2DTEMPLATE operator *(const T& escalar_derecha) const { return VEC_2DTEMPLATE(this->x * escalar_derecha, this->y * escalar_derecha); }	//OPERATOR DE PRODUCTO DE UN VECTOR Y ESCALAR.
	VEC_2DTEMPLATE operator /(const VEC_2DTEMPLATE& vec_derecha) const { return VEC_2DTEMPLATE(this->x / vec_derecha.x, this->y / vec_derecha.y); }	//OPERATOR DE COCIENTE DE VECTORES.
	VEC_2DTEMPLATE operator /(const T& escalar_derecha) const { return VEC_2DTEMPLATE(this->x / escalar_derecha, this->y / escalar_derecha); }	//OPERATOR DE COCIENTE DE UN VECTOR Y ESCALAR.
	VEC_2DTEMPLATE& operator += (const VEC_2DTEMPLATE& vec_derecha) { this->x += vec_derecha.x; this->y += vec_derecha.y; return *this; }	//OPERATOR DE ADICION SOBRE EL MISMO VECTOR.
	VEC_2DTEMPLATE& operator -= (const VEC_2DTEMPLATE& vec_derecha) { this->x -= vec_derecha.x; this->y -= vec_derecha.y; return *this; }	//OPERATOR DE SUBSTRACCION SOBRE EL MISMO VECTOR.
	VEC_2DTEMPLATE& operator *= (const T& escalar_derecha) { this->x *= escalar_derecha; this->y *= escalar_derecha; return *this; }	//OPERATOR DE PRODUCTO SOBRE EL MISMO VECTOR.
	VEC_2DTEMPLATE& operator /= (const T& escalar_derecha) { this->x /= escalar_derecha; this->y /= escalar_derecha; return *this; }	//OPERATOR DE COCIENTE SOBRE EL MISMO VECTOR.
	operator VEC_2DTEMPLATE<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; } //OPERATOR DE CASTING(INT_32) SOBRE EL MISMO VECTOR.
	operator VEC_2DTEMPLATE<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }	//OPERATOR DE CASTING(FLOAT) SOBRE EL MISMO VECTOR.
	operator VEC_2DTEMPLATE<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }	//OPERATOR DE CASTING(DOUBLE) SOBRE EL MISMO VECTOR.
};

template<class T> inline VEC_2DTEMPLATE<T> operator * (const float& lhs, const VEC_2DTEMPLATE<T>& rhs) { return VEC_2DTEMPLATE<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y)); }	//OPERATOR DE PRODUCTO FLOTANTE SOBRE 1 VECTORES Y 1 ESCALAR.
template<class T> inline VEC_2DTEMPLATE<T> operator * (const double& lhs, const VEC_2DTEMPLATE<T>& rhs) { return VEC_2DTEMPLATE<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y)); }	//OPERATOR DE PRODUCTO FLOTANTE DE DOBLE PRESICION SOBRE 1 VECTORES Y 1 ESCALAR.
template<class T> inline VEC_2DTEMPLATE<T> operator * (const int& lhs, const VEC_2DTEMPLATE<T>& rhs) { return VEC_2DTEMPLATE<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y)); }	//OPERATOR DE PRODUCTO ENTERO SOBRE 1 VECTORES Y 1 ESCALAR.
template<class T> inline VEC_2DTEMPLATE<T> operator / (const float& lhs, const VEC_2DTEMPLATE<T>& rhs) { return VEC_2DTEMPLATE<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y)); }	//OPERATOR DE COCIENTE FLOTANTE SOBRE 1 VECTORES Y 1 ESCALAR.
template<class T> inline VEC_2DTEMPLATE<T> operator / (const double& lhs, const VEC_2DTEMPLATE<T>& rhs) { return VEC_2DTEMPLATE<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y)); }	//OPERATOR DE COCIENTE FLOTANTE DE DOBLE PRESICION SOBRE 1 VECTORES Y 1 ESCALAR.
template<class T> inline VEC_2DTEMPLATE<T> operator / (const int& lhs, const VEC_2DTEMPLATE<T>& rhs) { return VEC_2DTEMPLATE<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y)); }	//OPERATOR DE COCIENTE FLOTANTE SOBRE 1 VECTORES Y 1 ESCALAR.

typedef VEC_2DTEMPLATE<int32_t> VECi_2D;	//DEFINIR UN TIPO PARA UN VECTOR ENTERO.
typedef VEC_2DTEMPLATE<uint32_t> VECui_2D;	//DEFINIR UN TIPO PARA UN VECTOR ENTERO SIN SIGNO.
typedef VEC_2DTEMPLATE<float> VECf_2D;	//DEFINIR UN TIPO PARA UN VECTOR FLOTANTE.
typedef VEC_2DTEMPLATE<double> VECd_2D;	//DEFINIR UN TIPO PARA UN VECTOR FLOTANTE DE DOBLE PRESICION.

static LRESULT CALLBACK windowEvent(HWND, UINT, WPARAM, LPARAM);

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
	MSG msg = {0};
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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