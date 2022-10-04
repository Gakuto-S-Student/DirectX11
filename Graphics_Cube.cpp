//==============================================================================
// Filename: Graphics_Cube.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Application.h"
#include "Graphics.h"
#include "Graphics_Shader.h"
#include "Graphics_Texture.h"

#include "Graphics_Cube.h"
using namespace DirectX;

// ���_�̍\����
struct Vertex3D
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};


// ���f���f�[�^
const Vertex3D g_CubeMeta[]
{
	{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}},
	{{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}},
	
	{{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},
	{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},
	
	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},
	
	{{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}},
	
	{{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},
	{{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}},

	{{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}},
	{{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}},

	{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}},
	{{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}},

	{{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}},
	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},

	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},

	{{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
	{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},

	{{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}},
	{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},

	{{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}},
	{{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}},
	{{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}},
};

// ����������
void GraphicsCube::Init()
{
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(Vertex3D) * ARRAYSIZE(g_CubeMeta);
	bufferDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = g_CubeMeta;					// �����Ƀ��f���f�[�^
	Graphics::Get()->Device()->CreateBuffer(&bufferDesc, &subResource, &m_vertexBuffer);

	// �e�N�X�`���̓ǂݍ��݂͍����ɒǉ�
	m_textureResource = GraphicsTexture::CreateTexture();

	GraphicsShader::LoadVertexAndLayout(&m_vertexShader, &m_vertexLayout);
	GraphicsShader::LoadPixelShader(&m_pixelShader);
}

// �I������
void GraphicsCube::Uninit()
{
	SAFE_RELEASE(m_textureResource);
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_vertexLayout);
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_pixelShader);
}

// �`�揈��
void GraphicsCube::Draw()
{
	Graphics::Get()->Context()->IASetInputLayout(m_vertexLayout);
	Graphics::Get()->Context()->VSSetShader(m_vertexShader, nullptr, 0);
	Graphics::Get()->Context()->PSSetShader(m_pixelShader, nullptr, 0);

	m_rotate.y += 0.01f;
	m_rotate.z += 0.01f;

	// �s��ϊ�(model)
	XMMATRIX translate, rotate, scale;
	translate = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	rotate    = XMMatrixRotationRollPitchYaw(m_rotate.x, m_rotate.y, m_rotate.z);
	scale     = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMMATRIX model = translate * rotate * scale;
	Graphics::Get()->SetModelMatrix(model);

	// �e�N�X�`���f�[�^�̑��M
	Graphics::Get()->Context()->PSSetShaderResources(0, 1, &m_textureResource);

	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	Graphics::Get()->Context()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	Graphics::Get()->Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Graphics::Get()->Context()->Draw(ARRAYSIZE(g_CubeMeta), 0);
}
