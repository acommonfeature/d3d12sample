#ifndef _WIN32_NATIVE_WINDOWS_H_
#define _WIN32_NATIVE_WINDOWS_H_

GRAPHIC_BEGIN_NAMESPACE(Graphic)

struct Win32NativeWindow
{
	void* hWnd = nullptr;

	Win32NativeWindow() noexcept
	{

	}

	explicit Win32NativeWindow(void* _hWnd) noexcept
		:hWnd(_hWnd)
	{

	}
};

GRAPHIC_END_NAMESPACE

#endif