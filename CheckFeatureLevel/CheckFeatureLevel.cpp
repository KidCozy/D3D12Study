﻿#pragma once
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

#include"DXUT/Core/d3dx12.h"

#include<exception>
#include<Windows.h>
#include<d3d12.h>
#include<d3dcompiler.h>
#include<dxgi.h>
#include <iostream>

#define HRCHECK(hr) { if(SUCCEEDED(hr)) { std::cout <<"S_OK"<<std::endl;} else { std::cout << "E_FAIL" << std::endl; return E_FAIL;} }
using namespace Microsoft::WRL;

// 기본 장치 (DXGI + D3DDevice)
IDXGIAdapter1* m_pAdapter = nullptr;
IDXGIFactory1* m_pFactory = nullptr;
ID3D12Device1* m_pDevice = nullptr;

// 커맨드 큐 (큐 + 리스트 + 얼로케이터)
ComPtr<ID3D12CommandQueue> m_pCommandQueue;
ID3D12CommandList* m_pCommandList;
ID3D12GraphicsCommandList* m_pGraphicsCMDList;
ID3D12CommandAllocator* m_pAllocator;



// 동기화 (펜스)
ID3D12Fence1* m_pFence;

void Release(); // 릴리즈 함수 전방선언

int main() {

	// 현재 펜스 값
	UINT m_CurrentFence = 0;

	// 서술자 (커맨드 큐, 어댑터)
	D3D12_COMMAND_QUEUE_DESC m_QueueDesc = {};
	DXGI_ADAPTER_DESC1 m_AdapterDesc;

	D3D12_FEATURE_DATA_FEATURE_LEVELS m_FeatureData;
	D3D_FEATURE_LEVEL m_RequiredLevels[3] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3

	};


	const D3D12_RESOURCE_TRANSITION_BARRIER m_ResourceTransitionBarrier;

	///---------------------------------///
	HRESULT hr;

	m_QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	m_QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	



	//// 팩토리 생성
	//hr = CreateDXGIFactory1(IID_PPV_ARGS(&m_pFactory));
	//HRCHECK(hr);

	//// 어댑터 열거
	//hr = m_pFactory->EnumAdapters1(0, &m_pAdapter);
	//HRCHECK(hr);

	//// 어댑터 서술자 초기화
	//m_pAdapter->GetDesc1(&m_AdapterDesc);

	// 장치 생성
	hr = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_pDevice));
	HRCHECK(hr);
	
	m_FeatureData.NumFeatureLevels = 3;
	m_FeatureData.pFeatureLevelsRequested = m_RequiredLevels;
	m_pDevice->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &m_FeatureData, sizeof(m_FeatureData));

	HRCHECK(m_pDevice->CreateCommandQueue(&m_QueueDesc, IID_PPV_ARGS(&m_pCommandQueue)));
	HRCHECK(m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, 
IID_PPV_ARGS(&m_pAllocator)));
	HRCHECK(m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pAllocator, NULL, IID_PPV_ARGS(&m_pCommandList)));
	//HRCHECK(m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pAllocator, NULL, IID_PPV_ARGS(&m_pGraphicsCMDList)));
//	HRCHECK(m_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence)));
	
	

	//m_pGraphicsCMDList->ResourceBarrier(1, )

    std::cout << "Hello Succeeded! \n";

	Release();
}

void Release() {
	m_pFactory->Release();
	m_pAdapter->Release();
	m_pDevice->Release();
	m_pAllocator->Release();
	m_pCommandList->Release();
	m_pGraphicsCMDList->Release();
	m_pFence->Release();
	

	std::cout << "Every COM objects were released." << std::endl;
}