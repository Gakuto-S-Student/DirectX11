//==============================================================================
// Filename: Graphics.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"
using namespace DirectX;

#define REF_RATE_DEN 1		// リフレッシュレート(分母)
#define REF_RATE_NUM 60		// リフレッシュレート(分子)


// クラスの実体取得
Graphics* Graphics::Get()
{
	static Graphics ret;
	return &ret;
}

// デバイスの取得
ID3D11Device* Graphics::Device()
{
	return m_device;
}

// コンテキストの取得
ID3D11DeviceContext* Graphics::Context()
{
	return m_context;
}

// DirectX11初期化処理
void Graphics::Init(int width, int height, HWND hWnd)
{
	this->CreateDeviceAndSwapChain(width, height, hWnd);
	this->CreateRenderTargetView();
	this->CreateDepthStencilView(width, height);
	this->CreateRasterizerState();
	this->CreateBlendState();
	this->CreateDepthStencilState();
	this->CreateSamplerState();
	this->CreateConstantBuffers();
	this->SetViewport(width, height);
}

// DirectX11終了処理
void Graphics::Uninit()
{
	SAFE_RELEASE(m_samplerState);
	SAFE_RELEASE(m_depthStencilState);
	SAFE_RELEASE(m_blendState);
	SAFE_RELEASE(m_rasterizerState);
	SAFE_RELEASE(m_depthStencilView);
	SAFE_RELEASE(m_renderTargetView);
	SAFE_RELEASE(m_swapChain);
	SAFE_RELEASE(m_context);
	SAFE_RELEASE(m_device);
}

// 画面クリア
void Graphics::Clear()
{
	float clearColor[4]{ 0.0f, 0.5f, 0.0f, 1.0f };
	m_context->ClearRenderTargetView(m_renderTargetView, clearColor);
	m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, D3D11_MAX_DEPTH, NULL);
}

// バッファの切り替え
void Graphics::Present()
{
	m_swapChain->Present(true, NULL);
}

// モデル行列の設定
void Graphics::SetModelMatrix(const DirectX::XMMATRIX model)
{
	XMMATRIX mat = XMMatrixTranspose(model);
	m_context->UpdateSubresource(m_modelMatrix, 0, nullptr, &mat, 0, 0);
}

// ビュー行列の設定
void Graphics::SetViewMatrix(const DirectX::XMMATRIX view)
{
	XMMATRIX mat = XMMatrixTranspose(view);
	m_context->UpdateSubresource(m_viewMatrix, 0, nullptr, &mat, 0, 0);
}

// プロジェクション行列の設定
void Graphics::SetProjectionMatrix(const DirectX::XMMATRIX projection)
{
	XMMATRIX mat = XMMatrixTranspose(projection);
	m_context->UpdateSubresource(m_projectionMatrix, 0, nullptr, &mat, 0, 0);
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
	HRESULT ret{};
	ID3D11Texture2D* p_renderTarget{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_renderTarget);
	ret = m_device->CreateRenderTargetView(p_renderTarget, nullptr, &m_renderTargetView);
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

// ラスタライザステートの生成
void Graphics::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc{};
	desc.CullMode           = D3D11_CULL_MODE::D3D11_CULL_BACK;
	desc.FillMode           = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	desc.DepthClipEnable    = true;
	desc.MultisampleEnable  = false;
	m_device->CreateRasterizerState(&desc, &m_rasterizerState);

	// ラスタライザステートの設定
	m_context->RSSetState(m_rasterizerState);
}

// ブレンドステートの生成
void Graphics::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable                 = false;
	blendDesc.IndependentBlendEnable                = false;
	blendDesc.RenderTarget[0].BlendEnable           = true;
	blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;                     // ピクセル シェーダーからのアルファ データ (A) です。ブレンディング前の処理無し
	blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;                 // ピクセル シェーダーからのアルファ データ (A) です。データが反転(1 - A)を生成
	blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;                     // 加算ブレンド
	blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND::D3D11_BLEND_ONE;                           // データ ソースの色は白 (1, 1, 1, 1) です。ブレンディング前の処理無し
	blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND::D3D11_BLEND_ZERO;                          // データ ソースの色は黒 (0, 0, 0, 0) です。ブレンディング前の処理無し。
	blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;                     // 加算ブレンド
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL; // 書き込みマスク_RGBA全て許可

	// ブレンドステートの作成処理
	m_device->CreateBlendState(&blendDesc, &m_blendState);

	// ブレンドステートの設定
	float blendFactor[]{ 0.0f, 0.0f, 0.0f, 0.0f };	// SrcBlend, DestBlendなどにD3D11_BLEND_BLEND_FACTORを使用した時のブレンディング係数(今回は使用しないので全てゼロでよい)
	m_context->OMSetBlendState(m_blendState, blendFactor, UINT_MAX);
}

// デプスステンシルステートの生成
void Graphics::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable    = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc      = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable  = false;
	m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);

	// デプスステンシルステートの設定
	m_context->OMSetDepthStencilState(m_depthStencilState, NULL);
}

// サンプラーステートの生成
void Graphics::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter   = D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;	// 線形補間
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	// サンプラーステートの生成
	m_device->CreateSamplerState(&samplerDesc, &m_samplerState);

	// サンプラーステートの設定
	m_context->PSSetSamplers(0, 1, &m_samplerState);
}

// 定数バッファの生成
void Graphics::CreateConstantBuffers()
{
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth            = sizeof(XMMATRIX);
	bufferDesc.Usage                = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags            = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags       = 0;
	bufferDesc.MiscFlags            = 0;
	bufferDesc.StructureByteStride  = sizeof(float);

	m_device->CreateBuffer(&bufferDesc, nullptr, &m_modelMatrix);
	m_device->CreateBuffer(&bufferDesc, nullptr, &m_viewMatrix);
	m_device->CreateBuffer(&bufferDesc, nullptr, &m_projectionMatrix);

	// 頂点シェーダのスロットに設定
	m_context->VSSetConstantBuffers(0, 1, &m_modelMatrix);      // 0番スロットに model matrix
	m_context->VSSetConstantBuffers(1, 1, &m_viewMatrix);       // 1番スロットに view matrix
	m_context->VSSetConstantBuffers(2, 1, &m_projectionMatrix); // 2番スロットに projection matrix 
}

// ビューポートの設定
void Graphics::SetViewport(const int width, const int height)
{
	D3D11_VIEWPORT viewport{};
	viewport.Width    = FLOAT(width);
	viewport.Height   = FLOAT(height);
	viewport.MaxDepth = D3D11_MAX_DEPTH;
	m_context->RSSetViewports(1, &viewport);
}
