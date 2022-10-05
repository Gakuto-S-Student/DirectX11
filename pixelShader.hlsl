//==============================================================================
// Filename: pixelShader.hlsl
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "common.hlsli"

Texture2D    g_Texture : register(t0);  /// �e�N�X�`���X���b�g
SamplerState g_Sampler : register(s0);  // �T���v���[

float4 main(PS_INPUT input) : SV_TARGET
{
    // �e�N�X�`������J���[���s�b�N
    float4 texColor = g_Texture.Sample(g_Sampler, input.TexCoord);
    
    return texColor;
}