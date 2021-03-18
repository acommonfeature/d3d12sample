#ifndef _D3D_SAMPLE_WIN_H_
#define _D3D_SAMPLE_WIN_H_

#include "d3dsamplebase.h"
#include "win32nativewindow.h"
#include "nativeappbase.h"

GRAPHIC_BEGIN_NAMESPACE(Graphic)

class D3DSampleWin final : public D3DSampleBase
{
public:
	virtual LRESULT HandleWin32Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SYSKEYDOWN:
			if ( (wParam == VK_RETURN)  && (lParam & (1 << 29)) )
			{
				ToggleFullScreenWindow();
				return 0;
			}
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			//case VK_F2:
			//{
			//	if ()
			//	{
			//	}
			//}
			default:
				break;
			}
		}

		struct WindowsMessageData
		{
			HWND hWnd;
			UINT message;
			WPARAM wParam;
			LPARAM lParam;
		}MsgData = { hWnd, message, wParam, lParam };
		
		//TODO:

	}

	virtual void OnWindowCreated(HWND hWnd, LONG WindowWidth, LONG WindowHeight)
	{
		m_hWnd = hWnd;

		try
		{
			Win32NativeWindow window{ hWnd };
			Initialize(&window);
		}
		catch (const std::exception&)
		{
			//LOG_ERROR("Failed to initialize Diligent Engine.");
		}
	}

protected:
	void ToggleFullScreenWindow()
	{
		if (fullScreenWindow)
		{
			return;
		}

		fullScreenWindow = !fullScreenWindow;

		if (fullScreenWindow)
		{
			GetWindowRect(m_hWnd, &windowRect);
			windowStyle = GetWindowLong(m_hWnd, GWL_STYLE);

			// Make the window borderless so that the client area can fill the screen.
			SetWindowLong(m_hWnd, GWL_STYLE, windowStyle & ~(WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME));

			DEVMODE devMode = {};
			devMode.dmSize = sizeof(DEVMODE);
			EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

			SetWindowPos(
				m_hWnd,
				HWND_TOPMOST,
				devMode.dmPosition.x,
				devMode.dmPosition.y,
				devMode.dmPosition.x + devMode.dmPelsWidth,
				devMode.dmPosition.y + devMode.dmPelsHeight,
				SWP_FRAMECHANGED | SWP_NOACTIVATE);

			ShowWindow(m_hWnd, SW_MAXIMIZE);
		}
		else
		{
			// Restore the window's attributes and size.
			SetWindowLong(m_hWnd, GWL_STYLE, windowStyle);

			SetWindowPos(
				m_hWnd,
				HWND_NOTOPMOST,
				windowRect.left,
				windowRect.top,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top,
				SWP_FRAMECHANGED | SWP_NOACTIVATE);

			ShowWindow(m_hWnd, SW_NORMAL);
		}
	}

	virtual void SetFullscreenMode()
	{
		if (fullScreenWindow)
		{
			ToggleFullScreenWindow();
		}
		//TODO:
		//D3DSampleBase::
	}

	virtual void SetWindowMode()
	{
		if (fullScreenWindow)
		{
			ToggleFullScreenWindow();
		}
		//TODO:
	}
	bool fullScreenWindow = false;
	HWND m_hWnd = 0;

public:
	virtual bool Initialize(const Win32NativeWindow* window);
	virtual void OnResize() override;
	virtual void Update();
	virtual void Render();

private:
	RECT windowRect = {};
	LONG windowStyle = 0;
};


GRAPHIC_END_NAMESPACE

#endif