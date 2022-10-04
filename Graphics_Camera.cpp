//==============================================================================
// Filename: Graphics_Camera.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"

#include "Graphics_Camera.h"
using namespace DirectX;

// ƒJƒƒ‰‚ÌÝ’èˆ—
void GraphicsCamera::Set3D(float fov, float aspect, float nearZ, float farZ)
{
	// s—ñ•ÏŠ·(view)
	XMMATRIX view = XMMatrixLookAtLH(
		{ 0.0f, 5.0f, -5.0f },
		{ 0.0f, 0.0f,  0.0f },
		{ 0.0f, 1.0f,  0.0f }
	);
	Graphics::Get()->SetViewMatrix(view);

	// s—ñ•ÏŠ·(projection)
	XMMATRIX proj = XMMatrixPerspectiveFovLH(
		fov,
		aspect,
		nearZ,
		farZ
	);
	Graphics::Get()->SetProjectionMatrix(proj);
}
