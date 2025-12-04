#include "Static_Common.hlsli"

PS_INPUT main(VS_INPUT V_INPUT)
{
    PS_INPUT OUT;
	
    float4 pos = V_INPUT.pos;
    float3 world_normal = V_INPUT.Norm;
    float3 world_tangent = V_INPUT.Tang;
	
    pos = mul(pos, mWorld);
    world_normal = mul(world_normal, (float3x3)mWorld); //이동성분은 필요없으니
    world_tangent = mul(world_tangent, (float3x3) mWorld); //이동성분은 필요없으니

	// Light or sth 
	// Normal
	// Tangent
	
    pos = mul(pos, mView);
    pos = mul(pos, mProj);

	
    OUT.pos  = pos;
    OUT.uv   = V_INPUT.uv;
    OUT.Tang = world_tangent;
    OUT.Norm = world_normal;

	
    return OUT;
}