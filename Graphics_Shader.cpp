//==============================================================================
// Filename: Graphics_Shader.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <fstream>
#include "Graphics.h"

#include "Graphics_Shader.h"

// ���_�V�F�[�_�̓ǂݍ��ݏ���
bool GraphicsShader::LoadVertexAndLayout(ID3D11VertexShader** vs, ID3D11InputLayout** layout)
{
	std::string buffer;
	if (!LoadFile("vertexShader.cso", buffer))
	{
		return false;
	}

	// ���_�V�F�[�_����
	Graphics::Get()->Device()->CreateVertexShader(buffer.c_str(), buffer.size(), nullptr, vs);
	

	D3D11_INPUT_ELEMENT_DESC elementDesc[]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	// ���_���C�A�E�g�ݒ�
	Graphics::Get()->Device()->CreateInputLayout(
		elementDesc,
		ARRAYSIZE(elementDesc),
		buffer.c_str(),
		buffer.size(),
		layout
	);

	return true;
}

// �s�N�Z���V�F�[�_�̓ǂݍ��ݏ���
bool GraphicsShader::LoadPixelShader(ID3D11PixelShader** ps)
{
	std::string buffer;
	if (!LoadFile("pixelShader.cso", buffer))
	{
		return false;
	}

	// �s�N�Z���V�F�[�_����
	Graphics::Get()->Device()->CreatePixelShader(buffer.c_str(), buffer.size(), nullptr, ps);
	return true;
}

// *.cso�t�@�C���ǂݍ���
bool GraphicsShader::LoadFile(const std::string fileName, std::string& buffer)
{
	std::ifstream ifs(fileName.c_str(), std::ios::binary);
	if (ifs.fail())
	{// �t�@�C���̃I�[�v���Ɏ��s
		return false;
	}

	ifs.seekg(0, std::ios::end);
	buffer.resize(size_t(ifs.tellg()));
	ifs.seekg(0, std::ios::beg);

	ifs.read(&buffer[0], buffer.size());
	ifs.close();

	return true;
}
