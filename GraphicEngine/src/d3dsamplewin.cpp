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

		//reset command list
		ThrowIfFailed(commandList->Reset(directCmdListAlloc.Get(), nullptr));

		BuildDescriptorHeaps();
		BuildConstantBuffers();
		BuildRootSignature();
		BuildShadersAndInputLayout();
		BuildBoxGeometry();
		BuildPSO();

		ThrowIfFailed(commandList->Close());
		ID3D12CommandList* cmdlists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(cmdlists), cmdlists);

		FlushCommandQueue();

		return true;
	}

	void D3DSampleWin::OnResize()
	{
		D3DSampleBase::OnResize();

		//window resized .update project matrix
		XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
		XMStoreFloat4x4(&mProj, P);
	}

	//int delte = 5;

	void D3DSampleWin::Update()
	{
		//update camera
		const auto& mouseState = inputController->GetMouseState();
		float mouseDeltaX = 0;
		float mouseDeltaY = 0;
		if (lastMouseState.PosX >= 0 && lastMouseState.PosY >=0 && 
			lastMouseState.ButtonFlags != MouseState::BUTTON_FLAG_NONE )
		{
			mouseDeltaX = mouseState.PosX - lastMouseState.PosX;
			mouseDeltaY = mouseState.PosY - lastMouseState.PosY;
		}

		if (mouseDeltaX != 0 || mouseDeltaY != 0)
		{
			int kk = 0;
		}

		lastMouseState = mouseState;

		constexpr float RotationSpeed = 0.005f;
		float yawDelta = mouseDeltaX * RotationSpeed;
		float pitchDelta = mouseDeltaY * RotationSpeed;

		if (mouseState.ButtonFlags & MouseState::BUTTON_FLAG_LEFT )
		{
			cameraYaw += yawDelta;
			cameraPitch += pitchDelta;
			//cameraPitch = (std::max)(cameraPitch, -MathHelper::Pi / 2.0f);
			//cameraPitch = (std::min)(cameraPitch, MathHelper::Pi / 2.0f);
		}

		// Apply extra rotations to adjust the view to match Khronos GLTF viewer
		cameraRotation =
			Quaternion::RotationFromAxisAngle(float3{ 1, 0, 0 }, -cameraPitch) *
			Quaternion::RotationFromAxisAngle(float3{ 0, 1, 0 }, -cameraYaw) *
			Quaternion::RotationFromAxisAngle(float3{ 0.75f, 0.0f, 0.75f }, PI_F);

		if (mouseState.ButtonFlags & MouseState::BUTTON_FLAG_RIGHT)
		{
			auto CameraView = cameraRotation.ToMatrix();
			auto CameraWorld = CameraView.Transpose();

			float3 CameraRight = float3::MakeVector(CameraWorld[0]);
			float3 CameraUp = float3::MakeVector(CameraWorld[1]);
			modelRotation =
				Quaternion::RotationFromAxisAngle(CameraRight, -pitchDelta) *
				Quaternion::RotationFromAxisAngle(CameraUp, -yawDelta) *
				modelRotation;
		}

		cameraDist -= mouseState.WheelDelta * 0.25f;
		//cameraDist = clamp(cameraDist, 0.1f, 5.f);

		float4x4 cameraView = cameraRotation.ToMatrix() * float4x4::Translation(0.f, 0.0f, cameraDist);

		mView = XMFLOAT4X4( cameraView.m00, cameraView.m01, cameraView.m02, cameraView.m03,
							cameraView.m10, cameraView.m11, cameraView.m12, cameraView.m13, 
							cameraView.m20, cameraView.m21, cameraView.m22, cameraView.m23, 
							cameraView.m30, cameraView.m31, cameraView.m32, cameraView.m33);
		//update matrix
		const float x = radius * sinf(phi) * cosf(theta);
		const float z = radius * sinf(phi) * sinf(theta);
		const float y = radius * cosf(phi);

		XMVECTOR pos = XMVectorSet(x, y, z, 1.0);
		XMVECTOR target = XMVectorZero();
		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0, 0.0);

		XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
		//XMStoreFloat4x4(&mView, view);

		XMMATRIX world = XMLoadFloat4x4(&mWorld);
		XMMATRIX proj = XMLoadFloat4x4(&mProj);
		view = XMLoadFloat4x4(&mView);
		auto worldViewProj = world * view * proj;

		ObjectConstants objConst;
		XMStoreFloat4x4(&objConst.WorldViewProj, XMMatrixTranspose(worldViewProj));

		objectCB->CopyData(0, objConst);
		//mouseState.WheelDelta = 0;

		inputController->ClearState();
	}

	void D3DSampleWin::Render()
	{
		//ThrowIfFailed(directCmdListAlloc->Reset());

		//ThrowIfFailed(commandList->Reset(directCmdListAlloc.Get(), nullptr));

		//commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		//	D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		//commandList->RSSetViewports(1, &screenViewport);
		//commandList->RSSetScissorRects(1, &scissorRect);

		////clear back buffer and depth buffer
		//const float color[] = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
		//commandList->ClearRenderTargetView(CurrentBackBufferView(), &color[0], 0, nullptr);
		//commandList->ClearDepthStencilView(DepthStencilView(),
		//	D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0, 0, 0, nullptr);

		////指定渲染目标
		//commandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
		////状态切换
		//commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		//	D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		////Done recording commands
		//ThrowIfFailed(commandList->Close());

		//ID3D12CommandList* cmdlists[] = { commandList.Get() };
		//commandQueue->ExecuteCommandLists(_countof(cmdlists), cmdlists);
		////swap
		//ThrowIfFailed(swapChain->Present(0, 0));
		//CurrBackBuffer = (CurrBackBuffer + 1) % SwapChainBufferCount;

		//FlushCommandQueue();

		ThrowIfFailed(directCmdListAlloc->Reset());

		ThrowIfFailed(commandList->Reset(directCmdListAlloc.Get(), pso.Get()));

		commandList->RSSetViewports(1, &screenViewport);
		commandList->RSSetScissorRects(1, &scissorRect);

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
			D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		commandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
		commandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0, 0, 0, nullptr);

		commandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

		ID3D12DescriptorHeap* descriptorHeaps[] = { cbvHeap.Get() };
		commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

		commandList->SetGraphicsRootSignature(rootSignature.Get());

		commandList->IASetVertexBuffers(0, 1, &boxGeo->VertexBufferView());
		commandList->IASetIndexBuffer(&boxGeo->IndexBufferView());
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->SetGraphicsRootDescriptorTable(0, cbvHeap->GetGPUDescriptorHandleForHeapStart());

		commandList->DrawIndexedInstanced(boxGeo->DrawArgs["box"].IndexCount, 1, 0, 0, 0);

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		ThrowIfFailed(commandList->Close());

		ID3D12CommandList* cmdslist[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(cmdslist), cmdslist);

		ThrowIfFailed(swapChain->Present(0, 0));

		CurrBackBuffer = (CurrBackBuffer + 1) % SwapChainBufferCount;

		FlushCommandQueue();
	}

	void D3DSampleWin::BuildDescriptorHeaps()
	{
		D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
		cbvHeapDesc.NumDescriptors = 1;
		cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		cbvHeapDesc.NodeMask = 0;
		ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&cbvHeapDesc,
			IID_PPV_ARGS(&cbvHeap)));
	}

	void D3DSampleWin::BuildConstantBuffers()
	{
		objectCB = make_unique<UploadBuffer<ObjectConstants>>(d3dDevice.Get(), 1, true);

		UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));

		D3D12_GPU_VIRTUAL_ADDRESS cbAdress = objectCB->Resource()->GetGPUVirtualAddress();
		//offset to the ith object constant buffer in the buffer
		int boxCBufIndex = 0;
		cbAdress += boxCBufIndex * objCBByteSize;

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
		cbvDesc.BufferLocation = cbAdress;
		cbvDesc.SizeInBytes = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));

		d3dDevice->CreateConstantBufferView(&cbvDesc,
			cbvHeap->GetCPUDescriptorHandleForHeapStart());
	}

	void D3DSampleWin::BuildRootSignature()
	{
		//shader programs as a function
		//input resources as function parameters
		// root signature can be thought of as defining the function signature
		CD3DX12_ROOT_PARAMETER slotRootParameter[1];

		CD3DX12_DESCRIPTOR_RANGE cbvTable;
		cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
		slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);

		CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

		HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
			serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

		ThrowIfFailed(hr);

		ThrowIfFailed(d3dDevice->CreateRootSignature(
			0,
			serializedRootSig->GetBufferPointer(),
			serializedRootSig->GetBufferSize(),
			IID_PPV_ARGS(&rootSignature)));
	}

	void D3DSampleWin::BuildShadersAndInputLayout()
	{
		HRESULT hr = S_OK;

		vsByteCode = d3dUtil::CompileShader(L"../Shaders/color.hlsl", nullptr, "VS", "vs_5_0");
		psByteCode = d3dUtil::CompileShader(L"../Shaders/color.hlsl", nullptr, "PS", "ps_5_0");

		inputLayout = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
	}

	void D3DSampleWin::BuildBoxGeometry()
	{
		std::array<Vertex, 8> vertices =
		{
			Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
			Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
			Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
			Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
			Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
			Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
			Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
			Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
		};

		std::array<std::uint16_t, 36> indices =
		{
			// front face
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7
		};

		const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
		const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

		boxGeo = std::make_unique<MeshGeometry>();
		boxGeo->Name = "box";

		ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeo->VertexBufferCPU));
		CopyMemory(boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

		ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeo->IndexBufferCPU));
		CopyMemory(boxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

		boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(d3dDevice.Get(),
			commandList.Get(), vertices.data(), vbByteSize, boxGeo->VertexBufferUploader);

		boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(d3dDevice.Get(),
			commandList.Get(), indices.data(), ibByteSize, boxGeo->IndexBufferUploader);

		boxGeo->VertexByteStride = sizeof(Vertex);
		boxGeo->VertexBufferByteSize = vbByteSize;
		boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
		boxGeo->IndexBufferByteSize = ibByteSize;

		SubmeshGeometry subMesh;
		subMesh.IndexCount = (UINT)indices.size();
		subMesh.StartIndexLocation = 0;
		subMesh.BaseVertexLocation = 0;
		boxGeo->DrawArgs["box"] = subMesh;
	}

	void D3DSampleWin::BuildPSO()
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
		ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		psoDesc.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
		psoDesc.pRootSignature = rootSignature.Get();

		psoDesc.VS =
		{
			reinterpret_cast<BYTE*>(vsByteCode->GetBufferPointer()),
			vsByteCode->GetBufferSize()
		};

		psoDesc.PS = 
		{
			reinterpret_cast<BYTE*>(psByteCode->GetBufferPointer()),
			psByteCode->GetBufferSize()
		};

		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = backBufferFormat;
		psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
		psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
		psoDesc.DSVFormat = depthStencilFormat;
		ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso)));
	}

}