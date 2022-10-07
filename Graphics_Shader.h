//==============================================================================
// Filename: Graphics_Shader.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include <string>

class GraphicsShader
{
public:
	//---------------------------------------------
	/// Load vertex shader
	///
	/// \param[out] ( vs )
	/// \param[out] ( layout )
	///
	/// \return true on success
	//---------------------------------------------
	static bool LoadVertexAndLayout(
		/* [out] */ ID3D11VertexShader** vs,
		/* [out] */ ID3D11InputLayout** layout
	);
	
	//---------------------------------------------
	/// Load pixel shader
	///
	/// \param[out] ( ps )
	///
	/// \return true on success
	//---------------------------------------------
	static bool LoadPixelShader(
		/* [out] */ ID3D11PixelShader** ps
	);

private:
	//---------------------------------------------
	/// Load shader file
	///
	/// \param[in] ( fileName )
	/// \param[out] ( buffer )
	/// 
	/// \return true on success
	//---------------------------------------------
	static bool LoadFile(
		/* [in] */  const std::string fileName,
		/* [out] */ std::string& buffer
	);
};

