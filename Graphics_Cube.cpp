//==============================================================================
// Filename: Graphics_Cube.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"
#include "Graphics_Shader.h"

#include "Graphics_Cube.h"

struct Vector3
{
	float x;
	float y;
	float z;
};
struct Vector2
{
	float x;
	float y;
};

struct Vertex3D
{
	Vector3 pos;
	Vector2 uv;
};

Vertex3D g_CubeMeta[]
{
	{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
	{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
	{{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f}},
	{{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f}}
};

// 初期化処理
void GraphicsCube::Init()
{
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(Vertex3D) * ARRAYSIZE(g_CubeMeta);
	bufferDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = g_CubeMeta;					// ここにモデルデータ
	Graphics::Get()->Device()->CreateBuffer(&bufferDesc, &subResource, &m_vertexBuffer);

	GraphicsShader::LoadVertexAndLayout(&m_vertexShader, &m_vertexLayout);
	GraphicsShader::LoadPixelShader(&m_pixelShader);
}

// 終了処理
void GraphicsCube::Uninit()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_vertexLayout);
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_pixelShader);
}

// 描画処理
void GraphicsCube::Draw()
{
	Graphics::Get()->Context()->IASetInputLayout(m_vertexLayout);
	Graphics::Get()->Context()->VSSetShader(m_vertexShader, nullptr, 0);
	Graphics::Get()->Context()->PSSetShader(m_pixelShader, nullptr, 0);

	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	Graphics::Get()->Context()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	Graphics::Get()->Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Graphics::Get()->Context()->Draw(4, 0);
}
