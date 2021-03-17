#ifndef _D3D_SAMPLE_BASE_H_
#define _D3D_SAMPLE_BASE_H_

#include "commondefinitions.h"
#include <windows.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include "nativeappbase.h"
#include <string>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

GRAPHIC_BEGIN_NAMESPACE(Graphic)
class D3DSampleBase : public NativeAppbase
{
public:
	D3DSampleBase();
	virtual ~D3DSampleBase();
	
protected:
	bool appPaused = false;
	bool minimized = false;
	bool maxmized = false;
	bool resizing = false;
	bool fullScreenState = false;
public:
	virtual bool Initialize();
	 
	//int Run();

	//windows ´°¿ÚÏà¹Ø
protected:
	bool InitMainWindow();
	virtual void OnResize();
	virtual void Update();
	virtual void Render();
	virtual void Present();
	virtual void WindowResize(int width, int height);

	//virtual void OnMouseDown(WPARAM btnState, int x, int y);
	//virtual void OnMouseUp(WPARAM btnState, int x, int y);
	//virtual void OnMouseMove(WPARAM btnState, int x, int y);
protected:
	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSawpChain();
	void FlushCommandQueue();
	virtual void CreateRtvAndDsvDescriptorHeaps();

protected:
	bool m4xMsaaState = false;
	UINT m4xMsaaQuality = 0;

	Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	UINT64 currentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> directCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

	static const int SwapChainBufferCount = 2;
	int CurrBackBuffer = 0;

	Microsoft::WRL::ComPtr<ID3D12Resource> swapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	D3D12_VIEWPORT screenViewport;
	D3D12_RECT scissorRect;

	UINT rtvDescriptorSize = 0;
	UINT dsvDescriptorSize = 0;
	UINT cbvSrvUavDescriptorSize = 0;

	std::wstring mainWindowCaption = L"D3D App Tjy";
	D3D_DRIVER_TYPE d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_SNORM;
	DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	int clientWidth = 800;
	int clientHeight = 600;

};

GRAPHIC_END_NAMESPACE

#endif