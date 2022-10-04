//==============================================================================
// Filename: Graphics_Texture.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"

#include "Graphics_Texture.h"

// �e�N�X�`���̐�������
ID3D11ShaderResourceView* GraphicsTexture::CreateTexture()
{
	// ���ƍ���
	int width  = 256;
	int height = 256;

	// �������ރe�N�X�`���쐬
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width               = width;
	textureDesc.Height              = height;
	textureDesc.MipLevels           = 1;
	textureDesc.ArraySize           = 1;
	textureDesc.Format              = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count    = 1;
	textureDesc.SampleDesc.Quality  = 0;
	textureDesc.Usage               = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	textureDesc.BindFlags           = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	textureDesc.MiscFlags           = 0;
	
	ID3D11Texture2D* texture;
	HRESULT hr = Graphics::Get()->Device()->CreateTexture2D(&textureDesc, nullptr, &texture);
	if (!texture)
	{
		return nullptr;
	}
	
	// �e�N�X�`���ɏ������ޕ���
	D3D11_MAPPED_SUBRESOURCE msr;
	Graphics::Get()->Context()->Map(
		texture,
		0,
		D3D11_MAP::D3D11_MAP_WRITE_DISCARD,
		0,
		&msr
	);
	// �����ŏ�������
	BYTE* pBits = (BYTE*)msr.pData;
	
	DWORD white = 0xffffffff;
	DWORD black = 0xff000000;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			DWORD color = black;
			if (y < height / 2 && x < width / 2)
			{
				color = white;
			}
			else if (y > height / 2 && x > width / 2)
			{
				color = white;
			}
			memcpy((BYTE*)pBits + msr.RowPitch * y + x * 4, &color, sizeof(DWORD));
		}
	}
	Graphics::Get()->Context()->Unmap(texture, 0);

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC resourceDesc;
	resourceDesc.Format                     = textureDesc.Format;
	resourceDesc.ViewDimension              = D3D11_SRV_DIMENSION_TEXTURE2D;
	resourceDesc.Texture2D.MostDetailedMip  = 0;
	resourceDesc.Texture2D.MipLevels        = textureDesc.MipLevels;

	ID3D11ShaderResourceView* ret;
	Graphics::Get()->Device()->CreateShaderResourceView(texture, &resourceDesc, &ret);
	
	SAFE_RELEASE(texture);

    return ret;
}
