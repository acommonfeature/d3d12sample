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


}

void Graphic::D3DSampleBase::OnResize()
{

}

GRAPHIC_END_NAMESPACE