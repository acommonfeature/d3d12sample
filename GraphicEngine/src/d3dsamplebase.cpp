#include "d3dsamplebase.h"
#include "d3dutil.h"

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

bool D3DSampleBase::Initialize()
{
	if (!InitMainWindow())
		return false;

	if (!InitDirect3D())
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

void Graphic::D3DSampleBase::WindowResize(int width, int height)
{

}

void Graphic::D3DSampleBase::Present()
{

}

void Graphic::D3DSampleBase::Render()
{

}

void Graphic::D3DSampleBase::Update()
{

}

bool Graphic::D3DSampleBase::InitDirect3D()
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
	CreateSawpChain();
	CreateRtvAndDsvDescriptorHeaps();

	return true;
}

void Graphic::D3DSampleBase::FlushCommandQueue()
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

void Graphic::D3DSampleBase::CreateSawpChain()
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
	//scdesc.OutputWindow = 
	scdesc.Windowed = true;
	scdesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//swap chain 使用命令队列进行刷新
	ThrowIfFailed(dxgiFactory->CreateSwapChain(commandQueue.Get(),
		&scdesc,
		swapChain.GetAddressOf()));
}

void Graphic::D3DSampleBase::CreateCommandObjects()
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


void Graphic::D3DSampleBase::CreateRtvAndDsvDescriptorHeaps()
{

}

void Graphic::D3DSampleBase::OnResize()
{

}

GRAPHIC_END_NAMESPACE