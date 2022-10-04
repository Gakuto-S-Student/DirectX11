struct VS_INPUT
{
    float4 Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct PS_INPUT
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD;
};

cbuffer g_modelBuffer : register(b0)
{
    matrix model;
}
cbuffer g_viewBuffer : register(b1)
{
    matrix view;
}
cbuffer g_projectionBuffer : register(b2)
{
    matrix projection;
}