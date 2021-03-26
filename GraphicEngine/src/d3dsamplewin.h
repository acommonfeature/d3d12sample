#ifndef _D3D_SAMPLE_WIN_H_
#define _D3D_SAMPLE_WIN_H_

#include <memory>
#include <vector>
#include "d3dsamplebase.h"
#include "win32nativewindow.h"
#include "nativeappbase.h"
#include "UploadBuffer.h"
#include <MathHelper.h>
#include "BasicMath.hpp"
#include "inputcontrollerwin.h"


using namespace std;
using namespace DirectX;

GRAPHIC_BEGIN_NAMESPACE(Graphic)

struct Vertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct ObjectConstants
{
	DirectX::XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

class D3DSampleWin final : public D3DSampleBase
{
public:
	D3DSampleWin()
	{
		inputController = make_unique<InputControllerWin>();
	}
	virtual~D3DSampleWin()
	{

	}
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

		if (inputController)
		{
			inputController->HandleNativeMessage(&MsgData);
		}
	
		return false;
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
			//LOG_ERROR("Failed to initialize Graphic Engine.");
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

public:
	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();


private:
	RECT windowRect = {};
	LONG windowStyle = 0;

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> cbvHeap = nullptr;

	std::unique_ptr<UploadBuffer<ObjectConstants>> objectCB = nullptr;

	unique_ptr<MeshGeometry> boxGeo = nullptr;

	Microsoft::WRL::ComPtr<ID3DBlob> vsByteCode = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> psByteCode = nullptr;

	vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pso = nullptr;

	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float theta = 1.5f * XM_PI;
	float phi = XM_PIDIV4;
	float radius = 5.0f;

	POINT lastMousePos;

	MouseState lastMouseState;
	float cameraDist = 8.0f;
	float cameraYaw = 0;
	float cameraPitch = 0;

	Quaternion cameraRotation = { 0, 0,0,1 };
	Quaternion modelRotation = Quaternion::RotationFromAxisAngle(float3{ 0.f, 1.0f, 0.0f }, -PI_F / 2.f);
};


GRAPHIC_END_NAMESPACE

#endif