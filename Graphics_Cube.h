//==============================================================================
// Filename: Graphics_Cube.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

class GraphicsCube
{
public:
	//---------------------------------------------
	/// Initialize Cube
	///
	/// \return	none
	//---------------------------------------------
	void Init();

	//---------------------------------------------
	/// Uninitialize Cube 
	///
	/// \return	none
	//---------------------------------------------
	void Uninit();

	//---------------------------------------------
	/// Draw Cube 
	///
	/// \return	none
	//---------------------------------------------
	void Draw();

private:
	ID3D11Buffer*             m_vertexBuffer;	    /// Vertices buffer
	ID3D11ShaderResourceView* m_textureResource;    /// Send to texture slot for pixel shader

	ID3D11InputLayout*	      m_vertexLayout;       /// A vertex layout
	ID3D11VertexShader*       m_vertexShader;       /// DirectX11 VertexShader interface
	ID3D11PixelShader*        m_pixelShader;        /// DirectX11 PixelShader interface

	DirectX::XMFLOAT3         m_rotate;             /// Rotate XYZ
};

