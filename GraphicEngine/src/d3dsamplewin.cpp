#include "d3dsamplewin.h"
#include "nativeappbase.h"
#include "d3dutil.h"
#include "d3dx12.h"

namespace Graphic
{
	NativeAppbase* CreateApplication()
	{
		return new D3DSampleWin;
	}

	bool D3DSampleWin::Initialize(const Win32NativeWindow* window)
	{
		if (!D3DSampleBase::Initialize(window))
			return false;

		return true;
	}

	void D3DSampleWin::OnResize()
	{
		D3DSampleBase::OnResize();
	}

	void D3DSampleWin::Update()
	{

	}

	void D3DSampleWin::Render()
	{
		ThrowIfFailed(directCmdListAlloc->Reset());

		ThrowIfFailed(commandList->Reset(directCmdListAlloc.Get(), nullptr));

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
			D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		commandList->RSSetViewports(1, &screenViewport);
		commandList->RSSetScissorRects(1, &scissorRect);

		//clear back buffer and depth buffer
		const float color[] = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
		commandList->ClearRenderTargetView(CurrentBackBufferView(), &color[0], 0, nullptr);
		commandList->ClearDepthStencilView(DepthStencilView(),
			D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0, 0, 0, nullptr);

		//指定渲染目标
		commandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
		//状态切换
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		//Done recording commands
		ThrowIfFailed(commandList->Close());

		ID3D12CommandList* cmdlists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(cmdlists), cmdlists);
		//swap
		ThrowIfFailed(swapChain->Present(0, 0));
		CurrBackBuffer = (CurrBackBuffer + 1) % SwapChainBufferCount;

		FlushCommandQueue();
	}

}