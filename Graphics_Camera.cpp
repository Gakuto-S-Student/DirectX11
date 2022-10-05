//==============================================================================
// Filename: Graphics_Camera.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"

#include "Graphics_Camera.h"
using namespace DirectX;

// �J�����̐ݒ菈��
void GraphicsCamera::Set3D(float fov, float aspect, float nearZ, float farZ)
{
	// �s��ϊ�(view)
	XMMATRIX view = XMMatrixLookAtLH(
		{ 0.0f, 5.0f, -5.0f },	// �J�����|�W�V����
		{ 0.0f, 0.0f,  0.0f },  // �����_
		{ 0.0f, 1.0f,  0.0f }   // ����
	);
	Graphics::Get()->SetViewMatrix(view);

	// �s��ϊ�(projection)
	XMMATRIX proj = XMMatrixPerspectiveFovLH(
		fov,
		aspect,
		nearZ,
		farZ
	);
	Graphics::Get()->SetProjectionMatrix(proj);
}
