#include "d3dsamplebase.h"
#include "d3dutil.h"
#include "d3dx12.h"

using Microsoft::WRL::ComPtr;
using namespace std;
//using namespace DirectX;

GRAPHIC_BEGIN_NAMESPACE(Graphic)

D3DSampleBase::D3DSampleBase()
{

}

D3DSampleBase::~D3DSampleBase()
{

}

bool D3DSampleBase::Initialize(const Win32NativeWindow* outWindow)
{
	//if (!InitMainWindow())
	//	return false;

	if (!InitDirect3D(*outWindow))
		return false;
	
	OnResize();

	return true;
}


bool D3DSampleBase::InitMainWindow()
{
	//WNDCLASS wc;
	//wc.style = CS_HREDRAW | CS_VREDRAW;
	//wc.lpfnWndProc = MsgProc;
	//wc.cbClsExtra = 0;
	//wc.cbWndExtra = 0;
	//wc.hInstance = mhAppInst;
	//wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	//wc.hCursor = LoadCursor(0, IDC_ARROW);
	//wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	//wc.lpszMenuName = 0;
	//wc.lpszClassName = L"MainWnd";

	return true;
}

ID3D12Resource* D3DSampleBase::CurrentBackBuffer() const
{
	return swapChainBuffer[CurrBackBuffer].Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE D3DSampleBase::DepthStencilView() const
{
	return dsvHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE D3DSampleBase::CurrentBackBufferView() const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		rtvHeap->GetCPUDescriptorHandleForHeapStart(),
		CurrBackBuffer,
		rtvDescriptorSize);
}

void D3DSampleBase::SetFullscreenModel()
{

}

void Graphic::D3DSampleBase::WindowResize(int width, int height)
{
	clientHeight = height;
	clientWidth = width;
	OnResize();
}

void D3DSampleBase::Present()
{

}

float Graphic::D3DSampleBase::AspectRatio() const
{
	return static_cast<float>(clientWidth / (float)clientHeight);
}

void D3DSampleBase::Render()
{

}

void D3DSampleBase::Update()
{

}

bool D3DSampleBase::InitDirect3D(const Win32NativeWindow& outWindow)
{
#if defined(DEBUG) || defined(_DEBUG)
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)));

	//创建硬件设备
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&d3dDevice)
	);

	// fallback to WRAP device
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWrapAdapter;
		ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWrapAdapter)));
		ThrowIfFailed(D3D12CreateDevice(pWrapAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&d3dDevice)));
	}

	ThrowIfFailed(d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));

	rtvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	dsvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	cbvSrvUavDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS qualityLevels;
	qualityLevels.Format = backBufferFormat;
	qualityLevels.SampleCount = 4;
	qualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	qualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(d3dDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&qualityLevels,
		sizeof(qualityLevels)));


	m4xMsaaQuality = qualityLevels.NumQualityLevels;
	assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");

#ifdef _DEBUG
	//LogAdapters();
#endif

	CreateCommandObjects();
	CreateSawpChain(outWindow);
	CreateRtvAndDsvDescriptorHeaps();

	return true;
}

void D3DSampleBase::FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	currentFence++;

	ThrowIfFailed(commandQueue->Signal(fence.Get(), currentFence));

	if ( fence->GetCompletedValue() < currentFence )
	{
		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

		ThrowIfFailed(fence->SetEventOnCompletion(currentFence, eventHandle));
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

void D3DSampleBase::CreateSawpChain(const Win32NativeWindow& outWindow)
{
	swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC scdesc;
	scdesc.BufferDesc.Width = clientWidth;
	scdesc.BufferDesc.Height = clientHeight;
	scdesc.BufferDesc.RefreshRate.Numerator = 60;
	scdesc.BufferDesc.RefreshRate.Denominator = 1;
	scdesc.BufferDesc.Format = backBufferFormat;
	scdesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scdesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scdesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	scdesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	scdesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scdesc.BufferCount = SwapChainBufferCount;
	scdesc.OutputWindow = reinterpret_cast<HWND>(outWindow.hWnd);
	scdesc.Windowed = true;
	scdesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//swap chain 使用命令队列进行刷新
	ThrowIfFailed(dxgiFactory->CreateSwapChain(commandQueue.Get(),
		&scdesc,
		swapChain.GetAddressOf()));
}

void D3DSampleBase::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)));

	ThrowIfFailed(d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(directCmdListAlloc.GetAddressOf())));

	ThrowIfFailed(d3dDevice->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		directCmdListAlloc.Get(),
		nullptr,
		IID_PPV_ARGS(commandList.GetAddressOf())));

	// Start off in a closed state.  This is because the first time we refer 
	// to the command list we will Reset it, and it needs to be closed before
	// calling Reset.
	//初始化时是关闭状态。 在reset()之前需要先关闭
	commandList->Close();
}


void D3DSampleBase::CreateRtvAndDsvDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&rtvHeapDesc,
		IID_PPV_ARGS(rtvHeap.GetAddressOf())));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;

	ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&dsvHeapDesc,
		IID_PPV_ARGS(dsvHeap.GetAddressOf())));
}

void D3DSampleBase::OnResize()
{
	assert(d3dDevice);
	assert(swapChain);
	assert(directCmdListAlloc);

	FlushCommandQueue();

	ThrowIfFailed(commandList->Reset(directCmdListAlloc.Get(), nullptr));

	for (int i = 0; i < SwapChainBufferCount; ++i)
	{
		swapChainBuffer[i].Reset();
	}
	depthStencilBuffer.Reset();

	//Resize the swapChain
	ThrowIfFailed(swapChain->ResizeBuffers(
		SwapChainBufferCount,
		clientWidth, clientHeight,
		backBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

	CurrBackBuffer = 0;

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i< SwapChainBufferCount; ++i)
	{
		ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&swapChainBuffer[i])));
		d3dDevice->CreateRenderTargetView(swapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, rtvDescriptorSize);
	}

	//Create depth/stencil buffer and view
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = clientWidth;
	depthStencilDesc.Height = clientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

		//SSAO chapter requires an SRV to the depth buffer to read from
		// the depth buffer.  Therefore, because we need to create two views to the same resource:
		//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
		//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
		// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = depthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	//D3D12_HEAP_PROPERTIES heapProps;
	//heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	//heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	//heapProps.CreationNodeMask = 1;
	//heapProps.VisibleNodeMask = 1;

	ThrowIfFailed(d3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(depthStencilBuffer.GetAddressOf())));

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = depthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	d3dDevice->CreateDepthStencilView(depthStencilBuffer.Get(), &dsvDesc, DepthStencilView());

	//Transition the resource
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(depthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	//Execute the resize commands;
	ThrowIfFailed(commandList->Close());
	ID3D12CommandList* cmdLists[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	//同步
	FlushCommandQueue();

	//Update the viewport transform
	screenViewport.TopLeftX = 0;
	screenViewport.TopLeftY = 0;
	screenViewport.Width = static_cast<float>(clientWidth);
	screenViewport.Height = static_cast<float>(clientHeight);
	screenViewport.MinDepth = 0.0f;
	screenViewport.MaxDepth = 1.0f;

	scissorRect = { 0, 0, clientWidth, clientHeight };
}

GRAPHIC_END_NAMESPACE