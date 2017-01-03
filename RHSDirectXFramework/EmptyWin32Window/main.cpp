#include <Windows.h>
#include <tchar.h>

// ISO C/C++ standard modules.
#include <cstdio>

static BOOL fDone = FALSE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		// Destroy allocated things
		fDone = TRUE;

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

// This Showing Window example is based on MSDN (https://msdn.microsoft.com/en-us/library/bb384843.aspx)

int main()
{
	static TCHAR szWindowClass[] = _T("win32app");
	static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= GetModuleHandle(nullptr);
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		MessageBox(nullptr, 
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			MB_OK);

		return 1;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		nullptr, nullptr, wcex.hInstance, nullptr);
	if (!hWnd) {
		MessageBox(nullptr,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			MB_OK);

		return 1;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;

	fDone = FALSE;
	while (!fDone) {
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(szWindowClass, wcex.hInstance);

	return 0;
}