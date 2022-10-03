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
		ID3D11VertexShader** vs,    /* [out] */
		ID3D11InputLayout** layout  /* [out] */
	);
	
	//---------------------------------------------
	/// Load pixel shader
	///
	/// \param[out] ( ps )
	///
	/// \return true on success
	//---------------------------------------------
	static bool LoadPixelShader(
		ID3D11PixelShader** ps  /* [out] */
	);

private:
	//---------------------------------------------
	/// Load pixel shader
	///
	/// \param[in] ( fileName )
	/// \param[out] ( buffer )
	/// 
	/// \return true on success
	//---------------------------------------------
	static bool LoadFile(
		const std::string fileName, /* [in] */
		std::string& buffer         /* [out] */
	);
};

