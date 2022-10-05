//==============================================================================
// Filename: Graphics_Texture.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

class GraphicsTexture
{
public:
	//---------------------------------------------
	/// Creat texture of check pattern	
	/// 
	/// \return	ResourceView pointer
	//---------------------------------------------
	static ID3D11ShaderResourceView* CreateTexture();
};

