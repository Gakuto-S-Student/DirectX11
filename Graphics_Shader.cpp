//==============================================================================
// Filename: Graphics_Shader.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <fstream>
#include "Graphics.h"

#include "Graphics_Shader.h"

// 頂点シェーダの読み込み処理
bool GraphicsShader::LoadVertexAndLayout(ID3D11VertexShader** vs, ID3D11InputLayout** layout)
{
	std::string buffer;
	if (!LoadFile("vertexShader.cso", buffer))
	{
		return false;
	}

	// 頂点シェーダ生成
	Graphics::Get()->Device()->CreateVertexShader(buffer.c_str(), buffer.size(), nullptr, vs);
	

	D3D11_INPUT_ELEMENT_DESC elementDesc[]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	// 頂点レイアウト設定
	Graphics::Get()->Device()->CreateInputLayout(
		elementDesc,
		ARRAYSIZE(elementDesc),
		buffer.c_str(),
		buffer.size(),
		layout
	);

	return true;
}

// ピクセルシェーダの読み込み処理
bool GraphicsShader::LoadPixelShader(ID3D11PixelShader** ps)
{
	std::string buffer;
	if (!LoadFile("pixelShader.cso", buffer))
	{
		return false;
	}

	// ピクセルシェーダ生成
	Graphics::Get()->Device()->CreatePixelShader(buffer.c_str(), buffer.size(), nullptr, ps);
	return true;
}

// *.csoファイル読み込み
bool GraphicsShader::LoadFile(const std::string fileName, std::string& buffer)
{
	std::ifstream ifs(fileName.c_str(), std::ios::binary);
	if (ifs.fail())
	{// ファイルのオープンに失敗
		return false;
	}

	ifs.seekg(0, std::ios::end);
	buffer.resize(size_t(ifs.tellg()));
	ifs.seekg(0, std::ios::beg);

	ifs.read(&buffer[0], buffer.size());
	ifs.close();

	return true;
}
