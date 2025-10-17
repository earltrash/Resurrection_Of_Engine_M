//
//
// Demo.fx : �⺻ ���̴� �ҽ�.
//
// 2003.11.4. Kihong Kim / mad_dog@hanmail.net
// 2010.12.01. Update. (DX11.Jun.2010)
// 2016.12.27. Update. (DX11. Windows SDK 8.1)
//


// ��� ����
cbuffer cbDEFAULT : register(b0)
{
    matrix mTM;     //���� ���. 
    matrix mView;   //�� ��ȯ ���. 
    matrix mProj;   //���� ��ȯ ���. 
    matrix mWV; //����-�� ��ȯ ���. 
    
    float4 col;
};


 
//VS ��� ����ü.
struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 uv : TEXCOORD0;
};


// ���� ó�� �Լ�.
float4 Light(float4 nrm);




////////////////////////////////////////////////////////////////////////////// 
//
// Vertex Shader Main : ���� ���̴� ���� �Լ�.
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
    
    //if (g_Lit.bOn) diff = Light(nor0); //���� �븻�� ���� �� �ƴѰ� 


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
// Pixel Shader Main : �ȼ� ���̴� ���� �Լ�.
//
////////////////////////////////////////////////////////////////////////////// 

float4 PS_Main(
				float4 pos : SV_POSITION,   //[�Է�] (������) �ȼ��� ��ǥ. (Screen, 2D)
				float4 diff : COLOR0, //[�Է�] (������) �ȼ��� ����. (Pixel Color : "Diffuse")
                 float2 uv : TEXCOORD0
				) : SV_TARGET               //[���] ����.(�ʼ�), "����Ÿ��" ���� ����մϴ�.
{
    float4 tex = 1;
    
        tex = texDiff.Sample(smpLinear, uv);
	 
    float4 col = tex * diff;
    
    
    return col;
}



/**************** end of file "Demo.fx" ***********************/
