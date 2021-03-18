#ifndef _NATIVE_APP_BASE_H_
#define _NATIVE_APP_BASE_H_

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <windows.h>


namespace Graphic
{
	class NativeAppbase
	{
	public:
		virtual~ NativeAppbase(){}
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Present() = 0;
		virtual void WindowResize(int width, int height) = 0;
		//Called by the framework after the window has been created.
		virtual void OnWindowCreated(HWND hWnd, LONG WindowWidth, LONG WindowHeight) = 0;

		//Handle Wind32 message
		virtual LRESULT HandleWin32Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			return 0;
		}
	};

	extern NativeAppbase* CreateApplication();
}

#endif