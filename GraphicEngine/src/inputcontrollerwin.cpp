#include "inputcontrollerwin.h"
#include <algorithm>

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include "windows.h"



namespace Graphic
{
	InputKeys MapCameraKeyWnd(UINT nKey)
	{
		switch (nKey)
		{
		case VK_CONTROL:
			return InputKeys::ControlDown;

		case VK_SHIFT:
			return InputKeys::ShiftDown;

		case VK_MENU:
			return InputKeys::AltDown;

		case VK_LEFT:
		case 'A':
			return InputKeys::MoveLeft;

		case VK_RIGHT:
		case 'D':
			return InputKeys::MoveRight;

		case VK_UP:
		case 'W':
			return InputKeys::MoveForward;

		case VK_DOWN:
		case 'S':
			return InputKeys::MoveBackward;

		case VK_PRIOR:
		case 'E':
			return InputKeys::MoveUp; // pgup

		case VK_NEXT:
		case 'Q':
			return InputKeys::MoveDown; // pgdn

		case VK_HOME:
			return InputKeys::Reset;

		case VK_ADD:
			return InputKeys::ZoomIn;

		case VK_SUBTRACT:
			return InputKeys::ZoomOut;

		default:
			return InputKeys::Unknown;
		}
	}


	InputControllerWin::InputControllerWin()
	{
		UpdateMousePos();
	}

	const MouseState& InputControllerWin::GetMouseState()
	{
		UpdateMousePos();
		return InputControllerBase::GetMouseState();
	}

	bool InputControllerWin::HandleNativeMessage(const void* MsgData)
	{
		mouseState.WheelDelta = 0;

		struct WindowMessageData
		{
			HWND   hWnd;
			UINT   message;
			WPARAM wParam;
			LPARAM lParam;
		};
		const WindowMessageData& WndMsg = *reinterpret_cast<const WindowMessageData*>(MsgData);

		auto hWnd = WndMsg.hWnd;
		auto uMsg = WndMsg.message;
		auto wParam = WndMsg.wParam;
		auto lParam = WndMsg.lParam;


		bool MsgHandled = false;
		switch (uMsg)
		{
		case WM_KEYDOWN:
		{
			// Map this key to a InputKeys enum and update the
			// state of m_aKeys[] by adding the INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN|INPUT_KEY_STATE_FLAG_KEY_IS_DOWN mask
			// only if the key is not down
			auto mappedKey = MapCameraKeyWnd((UINT)wParam);
			if (mappedKey != InputKeys::Unknown && mappedKey < InputKeys::TotalKeys)
			{
				auto& Key = keys[static_cast<int32_t>(mappedKey)];
				Key &= ~INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN;
				Key |= INPUT_KEY_STATE_FLAG_KEY_IS_DOWN;
			}
			MsgHandled = true;
			break;
		}

		case WM_KEYUP:
		{
			// Map this key to a InputKeys enum and update the
			// state of m_aKeys[] by removing the INPUT_KEY_STATE_FLAG_KEY_IS_DOWN mask.
			auto mappedKey = MapCameraKeyWnd((UINT)wParam);
			if (mappedKey != InputKeys::Unknown && mappedKey < InputKeys::TotalKeys)
			{
				auto& Key = keys[static_cast<int32_t>(mappedKey)];
				Key &= ~INPUT_KEY_STATE_FLAG_KEY_IS_DOWN;
				Key |= INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN;
			}
			MsgHandled = true;
			break;
		}

		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_LBUTTONDBLCLK:
		{
			// Update member var state
			if ((uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK))
			{
				mouseState.ButtonFlags |= MouseState::BUTTON_FLAG_LEFT;
			}
			if ((uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK))
			{
				mouseState.ButtonFlags |= MouseState::BUTTON_FLAG_MIDDLE;
			}
			if ((uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK))
			{
				mouseState.ButtonFlags |= MouseState::BUTTON_FLAG_RIGHT;
			}

			// Capture the mouse, so if the mouse button is
			// released outside the window, we'll get the WM_LBUTTONUP message
			SetCapture(hWnd);
			UpdateMousePos();

			MsgHandled = true;
			break;
		}

		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_LBUTTONUP:
		{
			// Update member var state
			if (uMsg == WM_LBUTTONUP)
			{
				mouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_LEFT;
			}
			if (uMsg == WM_MBUTTONUP)
			{
				mouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_MIDDLE;
			}
			if (uMsg == WM_RBUTTONUP)
			{
				mouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_RIGHT;
			}

			// Release the capture if no mouse buttons down
			if ((mouseState.ButtonFlags & (MouseState::BUTTON_FLAG_LEFT | MouseState::BUTTON_FLAG_MIDDLE | MouseState::BUTTON_FLAG_RIGHT)) == 0)
			{
				ReleaseCapture();
			}

			MsgHandled = true;
			break;
		}

		case WM_CAPTURECHANGED:
		{
			if ((HWND)lParam != hWnd)
			{
				if ((mouseState.ButtonFlags & MouseState::BUTTON_FLAG_LEFT) ||
					(mouseState.ButtonFlags & MouseState::BUTTON_FLAG_MIDDLE) ||
					(mouseState.ButtonFlags & MouseState::BUTTON_FLAG_RIGHT))
				{
					mouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_LEFT;
					mouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_MIDDLE;
					mouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_RIGHT;
					ReleaseCapture();
				}
			}

			MsgHandled = true;
			break;
		}

		case WM_MOUSEWHEEL:
			// Update member var state
			mouseState.WheelDelta = (float)((short)HIWORD(wParam)) / (float)WHEEL_DELTA;
			MsgHandled = true;
			break;

		case WM_MOUSEMOVE:
			UpdateMousePos();
			MsgHandled = true;
			break;
		}

		return MsgHandled;
	}

	void InputControllerWin::UpdateMousePos()
	{
		POINT MousePosition;
		GetCursorPos(&MousePosition);
		ScreenToClient(GetActiveWindow(), &MousePosition);
		mouseState.PosX = static_cast<float>(MousePosition.x);
		mouseState.PosY = static_cast<float>(MousePosition.y);

		/*if( m_bResetCursorAfterMove )
		{
			// Set position of camera to center of desktop,
			// so it always has room to move.  This is very useful
			// if the cursor is hidden.  If this isn't done and cursor is hidden,
			// then invisible cursor will hit the edge of the screen
			// and the user can't tell what happened
			POINT ptCenter;

			// Get the center of the current monitor
			MONITORINFO mi;
			mi.cbSize = sizeof( MONITORINFO );
			DXUTGetMonitorInfo( DXUTMonitorFromWindow( DXUTGetHWND(), MONITOR_DEFAULTTONEAREST ), &mi );
			ptCenter.x = ( mi.rcMonitor.left + mi.rcMonitor.right ) / 2;
			ptCenter.y = ( mi.rcMonitor.top + mi.rcMonitor.bottom ) / 2;
			SetCursorPos( ptCenter.x, ptCenter.y );
			m_ptLastMousePosition = ptCenter;
		}*/
	}
}

