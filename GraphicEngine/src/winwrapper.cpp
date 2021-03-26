#include <memory>
#include <iomanip>
#include <iostream>

#include <windows.h>
#include <crtdbg.h>
#include "nativeappbase.h"
#include "d3dsamplebase.h"

using namespace Graphic;
using namespace std;

std::unique_ptr<NativeAppbase> g_pTheApp;

LRESULT CALLBACK MessageProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#if defined(_DEBUG) || defined(DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	g_pTheApp.reset(CreateApplication());

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MessageProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"SampleApp";

	RegisterClass(&wc);

	int desireddWidth = 0;
	int desiredHeight = 0;
	//g_pTheApp->
	LONG windowWidth   = 800;
	LONG windowHeight  = 600;
	RECT rc = { 0, 0, windowWidth, windowHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	HWND wnd = CreateWindow( L"SampleApp", L"DX12 Sample By Tang",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, 0, 0, hInstance, 0);

	if (!wnd)
	{
		//std:::cerr << "Failed to create a window";
		return 1;
	}

	g_pTheApp->OnWindowCreated(wnd, windowWidth, windowHeight);

	ShowWindow(wnd, nShowCmd);
	UpdateWindow(wnd);

	

	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (g_pTheApp)
			{
				g_pTheApp->Update();
				g_pTheApp->Render();
				g_pTheApp->Present();
			}
		}

	}

	g_pTheApp.reset();
	return (int)msg.wParam;
}

LRESULT CALLBACK MessageProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pTheApp)
	{
		auto res = g_pTheApp->HandleWin32Message(wnd, message, wParam, lParam);
		if (res != 0)
			return res;
	}

	switch (message)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(wnd, &ps);
		EndPaint(wnd, &ps);
		return 0;
	case WM_SIZE:
		if (g_pTheApp)
		{
			g_pTheApp->WindowResize(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;
	case WM_CHAR:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 320;
		lpMMI->ptMinTrackSize.y = 240;
		return 0;
	}
	//case WM_MOUSEMOVE:
		//g_pTheApp->OnMouseMove();
	default:
		return DefWindowProc(wnd, message, wParam, lParam);
	}
}