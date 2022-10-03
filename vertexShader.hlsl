#include "common.hlsli"

PS_INPUT main( VS_INPUT input )
{
    PS_INPUT output;
    
    output.Position = input.Position;
    output.TexCoord = input.TexCoord;
    
	return output;
}