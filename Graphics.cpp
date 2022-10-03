//==============================================================================
// Filename: Graphics.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"

#define REF_RATE_DEN 1		// リフレッシュレート(分母)
#define REF_RATE_NUM 60		// リフレッシュレート(分子)


// クラスの実体取得
Graphics* Graphics::Get()
{
	static Graphics ret;
	return &ret;
}

// DirectX11初期化処理
void Graphics::Init(int width, int height, HWND hWnd)
{
	this->CreateDeviceAndSwapChain(width, height, hWnd);
	this->CreateRenderTargetView();
	this->CreateDepthStencilView(width, height);
}

// DirectX11終了処理
void Graphics::Uninit()
{
	SAFE_RELEASE(m_swapChain);
	SAFE_RELEASE(m_context);
	SAFE_RELEASE(m_device);
}

// 画面クリア
void Graphics::Clear()
{
	float clearColor[4]{ 0.0f, 0.5f, 0.0f, 1.0f };
	m_context->ClearRenderTargetView(m_renderTargetView, clearColor);
	m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1.0f, NULL);
}

// バッファの切り替え
void Graphics::Present()
{
	m_swapChain->Present(true, NULL);
}

// スワップチェインの生成
void Graphics::CreateDeviceAndSwapChain(int width, int heihgt, HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC desc{};
	desc.BufferCount                            = 1;
	desc.BufferDesc.Width                       = width;
	desc.BufferDesc.Height                      = heihgt;
	desc.BufferDesc.Format                      = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Denominator     = REF_RATE_DEN;
	desc.BufferDesc.RefreshRate.Numerator       = REF_RATE_NUM;
	desc.BufferUsage                            = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow                           = hWnd;
	desc.SampleDesc.Count                       = 1;
	desc.SampleDesc.Quality                     = 0;
	desc.Windowed                               = TRUE;

	// デバイスの生成
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		NULL,
		nullptr,
		NULL,
		D3D11_SDK_VERSION,
		&desc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_context
	);
}

// レンダーターゲットの生成
void Graphics::CreateRenderTargetView()
{
	ID3D11Texture2D* p_renderTarget{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_renderTarget);
	m_device->CreateRenderTargetView(p_renderTarget, nullptr, &m_renderTargetView);
}

// 深度バッファの生成
void Graphics::CreateDepthStencilView(const int width, const int height)
{
	ID3D11Texture2D* depthStencil{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width               = width;
	textureDesc.Height              = height;
	textureDesc.MipLevels           = 1;
	textureDesc.ArraySize           = 1;
	textureDesc.Format              = DXGI_FORMAT::DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc.Count    = 1;
	textureDesc.SampleDesc.Quality  = 0;
	textureDesc.Usage               = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags           = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags      = 0;
	textureDesc.MiscFlags           = 0;
	m_device->CreateTexture2D(&textureDesc, nullptr, &depthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format         = textureDesc.Format;
	viewDesc.ViewDimension  = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
	viewDesc.Flags          = 0;
	m_device->CreateDepthStencilView(depthStencil, &viewDesc, &m_depthStencilView);

	// レンダーターゲットに設定する
	m_context->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}
