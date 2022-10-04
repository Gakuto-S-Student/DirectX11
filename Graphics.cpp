//==============================================================================
// Filename: Graphics.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"
using namespace DirectX;

#define REF_RATE_DEN 1		// ���t���b�V�����[�g(����)
#define REF_RATE_NUM 60		// ���t���b�V�����[�g(���q)


// �N���X�̎��̎擾
Graphics* Graphics::Get()
{
	static Graphics ret;
	return &ret;
}

// �f�o�C�X�̎擾
ID3D11Device* Graphics::Device()
{
	return m_device;
}

// �R���e�L�X�g�̎擾
ID3D11DeviceContext* Graphics::Context()
{
	return m_context;
}

// DirectX11����������
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

// DirectX11�I������
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

// ��ʃN���A
void Graphics::Clear()
{
	float clearColor[4]{ 0.0f, 0.5f, 0.0f, 1.0f };
	m_context->ClearRenderTargetView(m_renderTargetView, clearColor);
	m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, D3D11_MAX_DEPTH, NULL);
}

// �o�b�t�@�̐؂�ւ�
void Graphics::Present()
{
	m_swapChain->Present(true, NULL);
}

// ���f���s��̐ݒ�
void Graphics::SetModelMatrix(const DirectX::XMMATRIX model)
{
	XMMATRIX mat = XMMatrixTranspose(model);
	m_context->UpdateSubresource(m_modelMatrix, 0, nullptr, &mat, 0, 0);
}

// �r���[�s��̐ݒ�
void Graphics::SetViewMatrix(const DirectX::XMMATRIX view)
{
	XMMATRIX mat = XMMatrixTranspose(view);
	m_context->UpdateSubresource(m_viewMatrix, 0, nullptr, &mat, 0, 0);
}

// �v���W�F�N�V�����s��̐ݒ�
void Graphics::SetProjectionMatrix(const DirectX::XMMATRIX projection)
{
	XMMATRIX mat = XMMatrixTranspose(projection);
	m_context->UpdateSubresource(m_projectionMatrix, 0, nullptr, &mat, 0, 0);
}

// �X���b�v�`�F�C���̐���
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

	// �f�o�C�X�̐���
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

// �����_�[�^�[�Q�b�g�̐���
void Graphics::CreateRenderTargetView()
{
	HRESULT ret{};
	ID3D11Texture2D* p_renderTarget{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_renderTarget);
	ret = m_device->CreateRenderTargetView(p_renderTarget, nullptr, &m_renderTargetView);
}

// �[�x�o�b�t�@�̐���
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

	// �����_�[�^�[�Q�b�g�ɐݒ肷��
	m_context->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}

// ���X�^���C�U�X�e�[�g�̐���
void Graphics::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc{};
	desc.CullMode           = D3D11_CULL_MODE::D3D11_CULL_BACK;
	desc.FillMode           = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	desc.DepthClipEnable    = true;
	desc.MultisampleEnable  = false;
	m_device->CreateRasterizerState(&desc, &m_rasterizerState);

	// ���X�^���C�U�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_rasterizerState);
}

// �u�����h�X�e�[�g�̐���
void Graphics::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable                 = false;
	blendDesc.IndependentBlendEnable                = false;
	blendDesc.RenderTarget[0].BlendEnable           = true;
	blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;                     // �s�N�Z�� �V�F�[�_�[����̃A���t�@ �f�[�^ (A) �ł��B�u�����f�B���O�O�̏�������
	blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;                 // �s�N�Z�� �V�F�[�_�[����̃A���t�@ �f�[�^ (A) �ł��B�f�[�^�����](1 - A)�𐶐�
	blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;                     // ���Z�u�����h
	blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND::D3D11_BLEND_ONE;                           // �f�[�^ �\�[�X�̐F�͔� (1, 1, 1, 1) �ł��B�u�����f�B���O�O�̏�������
	blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND::D3D11_BLEND_ZERO;                          // �f�[�^ �\�[�X�̐F�͍� (0, 0, 0, 0) �ł��B�u�����f�B���O�O�̏��������B
	blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;                     // ���Z�u�����h
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL; // �������݃}�X�N_RGBA�S�ċ���

	// �u�����h�X�e�[�g�̍쐬����
	m_device->CreateBlendState(&blendDesc, &m_blendState);

	// �u�����h�X�e�[�g�̐ݒ�
	float blendFactor[]{ 0.0f, 0.0f, 0.0f, 0.0f };	// SrcBlend, DestBlend�Ȃǂ�D3D11_BLEND_BLEND_FACTOR���g�p�������̃u�����f�B���O�W��(����͎g�p���Ȃ��̂őS�ă[���ł悢)
	m_context->OMSetBlendState(m_blendState, blendFactor, UINT_MAX);
}

// �f�v�X�X�e���V���X�e�[�g�̐���
void Graphics::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable    = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc      = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable  = false;
	m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	m_context->OMSetDepthStencilState(m_depthStencilState, NULL);
}

// �T���v���[�X�e�[�g�̐���
void Graphics::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter   = D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;	// ���`���
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	// �T���v���[�X�e�[�g�̐���
	m_device->CreateSamplerState(&samplerDesc, &m_samplerState);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_context->PSSetSamplers(0, 1, &m_samplerState);
}

// �萔�o�b�t�@�̐���
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

	// ���_�V�F�[�_�̃X���b�g�ɐݒ�
	m_context->VSSetConstantBuffers(0, 1, &m_modelMatrix);      // 0�ԃX���b�g�� model matrix
	m_context->VSSetConstantBuffers(1, 1, &m_viewMatrix);       // 1�ԃX���b�g�� view matrix
	m_context->VSSetConstantBuffers(2, 1, &m_projectionMatrix); // 2�ԃX���b�g�� projection matrix 
}

// �r���[�|�[�g�̐ݒ�
void Graphics::SetViewport(const int width, const int height)
{
	D3D11_VIEWPORT viewport{};
	viewport.Width    = FLOAT(width);
	viewport.Height   = FLOAT(height);
	viewport.MaxDepth = D3D11_MAX_DEPTH;
	m_context->RSSetViewports(1, &viewport);
}
