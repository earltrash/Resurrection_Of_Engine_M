#include "Static_Common.hlsli"

float4 main(PS_INPUT P_INPUT) : SV_TARGET
{
    float4 diffuse = tex_Albedo.Sample(samLinear, P_INPUT.uv);
	
    return diffuse;
}