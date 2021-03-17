#include <memory>
#include <iomanip>
#include <iostream>

#include <windows.h>
#include <crtdbg.h>
#include "nativeappbase.h"
#include "d3dsamplebase.h"

using namespace Graphic;

std::unique_ptr<NativeAppbase> g_pTheApp;

LRESULT CALLBACK MessageProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#if defined(_DEBUG) || defined(DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//g_pTheApp.reset(new D3DSampleBase());
}