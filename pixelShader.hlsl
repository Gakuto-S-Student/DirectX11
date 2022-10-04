#include "common.hlsli"

Texture2D    g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 texColor = g_Texture.Sample(g_Sampler, input.TexCoord);
    
    return texColor;
}