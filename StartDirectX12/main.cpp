#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace std;


void DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	printf(format, valist);
	va_end(valist);
#endif // _DEBUG

}

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	// ウインドウが破壊されたら呼ばれる
	if (msg == WM_DESTROY) {
		PostQuitMessage(0); // OSにたいして「もうこのアプリは終わる」と伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


#ifdef _DEBUG
int main() {
# else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
//	DebugOutputFormatString("Show window test.");
//	getchar();
	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;
	w.lpszClassName = "DXSample";
	w.hInstance = GetModuleHandle(nullptr);
	RegisterClassEx(&w);
	int window_width = 640;
	int window_height = 480;
	RECT wrc = { 0, 0, window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	HWND hwnd = CreateWindow(w.lpszClassName
		, "DX12テスト"
		, WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, wrc.right - wrc.left
		, wrc.bottom - wrc.top
		, nullptr
		, nullptr
		, w.hInstance
		, nullptr);
	ShowWindow(hwnd, SW_SHOW);
	MSG msg = {};
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			break;
		}
	}
	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}


