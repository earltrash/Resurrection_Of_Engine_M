//
//
// Demo.fx : 기본 셰이더 소스.
//
// 2003.11.4. Kihong Kim / mad_dog@hanmail.net
// 2010.12.01. Update. (DX11.Jun.2010)
// 2016.12.27. Update. (DX11. Windows SDK 8.1)
//


// 상수 버퍼
cbuffer cbDEFAULT : register(b0)
{
    matrix mTM;     //월드 행렬. 
    matrix mView;   //뷰 변환 행렬. 
    matrix mProj;   //투영 변환 행렬. 
    matrix mWV; //월드-뷰 변환 행렬. 
    
    float4 col;
};


 
//VS 출력 구조체.
struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 uv : TEXCOORD0;
};


// 조명 처리 함수.
float4 Light(float4 nrm);




////////////////////////////////////////////////////////////////////////////// 
//
// Vertex Shader Main : 정점 셰이더 메인 함수.
//
////////////////////////////////////////////////////////////////////////////// 

VSOutput VS_Main(
				 float4 pos : POSITION0,
                 float4 nor0 : COLOR0,
                 float2 uv0 : TEXCOORD0
				)
{
	
        
    pos.w = 1;
    
    pos = mul(pos, mTM);      
	
    pos = mul(pos, mView);
 
    pos = mul(pos, mProj);

    float4 diff = 1;   
    
    //if (g_Lit.bOn) diff = Light(nor0); //차피 노말은 같은 거 아닌가 


    VSOutput o = (VSOutput) 0;
    
    
    
    o.pos = pos;
    o.col = col;
    o.uv = uv0;
   
    
    
    return o;
}


Texture2D texDiff : register(t0);

SamplerState smpLinear : register(s0);


////////////////////////////////////////////////////////////////////////////// 
//
// Pixel Shader Main : 픽셀 셰이더 메인 함수.
//
////////////////////////////////////////////////////////////////////////////// 

float4 PS_Main(
				float4 pos : SV_POSITION,   //[입력] (보간된) 픽셀별 좌표. (Screen, 2D)
				float4 diff : COLOR0, //[입력] (보간된) 픽셀별 색상. (Pixel Color : "Diffuse")
                 float2 uv : TEXCOORD0
				) : SV_TARGET               //[출력] 색상.(필수), "렌더타겟" 으로 출력합니다.
{
    float4 tex = 1;
    
        tex = texDiff.Sample(smpLinear, uv);
	 
    float4 col = tex * diff;
    
    
    return col;
}



/**************** end of file "Demo.fx" ***********************/
