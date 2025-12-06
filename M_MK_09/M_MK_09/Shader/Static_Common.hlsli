//Constant Buffer List

Texture2D tex_Albedo : register(t0);
Texture2D tex_Normal : register(t1);
Texture2D tex_Specular : register(t2);
Texture2D tex_Emissive : register(t3);
Texture2D tex_Metal : register(t4);
Texture2D tex_Roughness : register(t5);
Texture2D tex_Opacity : register(t6);




//etc


SamplerState samLinear : register(s0);
//Clamp도 언젠간 쓰겠죠?

cbuffer cb_TransformMatrix : register(b0)
{
    matrix mWorld;
    
    matrix mView;
    matrix mProj;
    matrix mWVP;
    float4 col;
}

cbuffer cb_Light : register(b1)
{
    float4 Dir;
    float4 Diffuse;
    float4 Ambient;
    float Range;
    bool ONOFF;
}

//얘는 폐기 되었음.
cbuffer cb_Material : register(b2)
{
    float4 Diffuse_mtrl;
    float4 Ambient_mtrl;
    float4 Spec;
    float Power;
}

struct VS_INPUT
{
    float4 pos  : POSITIONT;
    float2 uv   :        UV;
    float3 Norm :    NORMAL;
    float3 Tang :   TANGENT;
};

//Texture를 기준으로 PS_INPUT을 빌드업 합시다. 

struct PS_INPUT
{
    float4 pos  : POSITIONT;
    float2 uv   :        UV;
    float3 Norm :    NORMAL;
    float3 Tang :   TANGENT;
};
