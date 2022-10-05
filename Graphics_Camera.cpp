//==============================================================================
// Filename: Graphics_Camera.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"

#include "Graphics_Camera.h"
using namespace DirectX;

// カメラの設定処理
void GraphicsCamera::Set3D(float fov, float aspect, float nearZ, float farZ)
{
	// 行列変換(view)
	XMMATRIX view = XMMatrixLookAtLH(
		{ 0.0f, 5.0f, -5.0f },	// カメラポジション
		{ 0.0f, 0.0f,  0.0f },  // 注視点
		{ 0.0f, 1.0f,  0.0f }   // 方向
	);
	Graphics::Get()->SetViewMatrix(view);

	// 行列変換(projection)
	XMMATRIX proj = XMMatrixPerspectiveFovLH(
		fov,
		aspect,
		nearZ,
		farZ
	);
	Graphics::Get()->SetProjectionMatrix(proj);
}
