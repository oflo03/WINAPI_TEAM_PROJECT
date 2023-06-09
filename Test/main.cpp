#include "game_framework.h"
#include"LogoState.h"
#include"Vector2D.h"
#include <crtdbg.h>

double frame_time;
extern std::vector<GameState*> stateStack;
HDC mDC;
Vector2D<float> monitorSize;
Vector2D<float> camSize;

HINSTANCE g_hinst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Drop The Gun";
RECT screen;
LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hinst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW / CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, NULL);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExW(&WndClass);

	HMONITOR hMonitor = MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(hMonitor, &monitorInfo);

	monitorSize = Vector2D<float>(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
	camSize = monitorSize /3;

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_POPUP,
		monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
		monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
		NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

double GetFrameTime()
{
	static LARGE_INTEGER frequency;
	static bool initialized = false;
	static LARGE_INTEGER prevTime;

	if (!initialized)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&prevTime);
		initialized = TRUE;
	}

	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double frameTime = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
	prevTime = currentTime;

	return frameTime;
}

LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &screen);
		start_game(new LogoState());
		SetTimer(hWnd, 1, 10, NULL);
		SetCursor(NULL);
		break;
	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, monitorSize.x, monitorSize.y);
		mDC = CreateCompatibleDC(hDC);
		SelectObject(mDC, hBitmap);
		stateStack.back()->draw();
		BitBlt(hDC, 0, 0, monitorSize.x, monitorSize.y, mDC, 0, 0, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(mDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		if (wParam == 1) {
			frame_time = GetFrameTime();
			stateStack.back()->handle_events();
			stateStack.back()->update();
			InvalidateRect(hWnd, NULL, false);
		}
		break;
	case WM_MOUSEWHEEL:
		break;
	case WM_DESTROY:
		end_game();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
