#pragma once
#include <vector>
#include <array>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "D3D11.h"
#include "DirectXMath.h"



using namespace DirectX;

typedef XMFLOAT4		COLOR;

struct PosNCol
{
	XMFLOAT3 pos;
	COLOR col;
};

struct PosNNor
{
	XMFLOAT3 pos;
	XMFLOAT3 nor;
};

struct Model_Prop
{
	ID3D11Buffer* m_pVB = nullptr;		//!< 정점 버퍼
	UINT			m_Size = 0;			//!< 버퍼 전체 크기(바이트)
	UINT			m_Stride = 0;	    //!< 정점 크기.
	UINT			m_Offset = 0;		//!< 렌더링 시작 정점 (offset)
	UINT			m_VtxCnt = 0;		//!< 정점 개수.
};

#pragma region VertexFlags

enum class VertexFlag : uint32_t
{
	VF_NONE = 0,

	VF_POSITION = 1 << 0,  // 0x00000001 (Pos)
	VF_NORMAL = 1 << 1,  // 0x00000002 (Nor)
	VF_TEXCOORD = 1 << 2,  // 0x00000004 (UV/Tex)
	VF_COLOR = 1 << 3,  // 0x00000008 (Color)


	VF_POSCOL = VF_POSITION | VF_COLOR,

	VF_POSNOR = VF_POSITION | VF_NORMAL,

	VK_POSCOLNOR = VF_POSITION | VF_COLOR | VF_NORMAL,



	VF_POSCOLTEX = VF_POSITION | VF_COLOR | VF_TEXCOORD,

#pragma region later
	// 3. PBR / 노멀 매핑 속성
	//VF_TANGENT = 1 << 4,  // 0x00000010 (Tangent)
	//VF_BINORMAL = 1 << 5,  // 0x00000020 (BiNormal/BiTangent)

	//// 4. 애니메이션 속성 (스킨드 메쉬에 필수)
	//VF_BONE_ID = 1 << 6,  // 0x00000040 (Bone Indices)
	//VF_WEIGHT = 1 << 7,  // 0x00000080 (Bone Weights)

	//// 5. 기타 (추후 확장 가능)
	//VF_VELOCITY = 1 << 8,  // 0x00000100 (모션 블러 등)

	//// A. 단순 렌더링 (Basic Unlit)
	//VF_BASIC = VF_POSITION | VF_TEXCOORD,

	//// B. 표준 라이팅 모델 (Phong/Blinn-Phong)
	//VF_STANDARD = VF_POSITION | VF_NORMAL | VF_TEXCOORD,

	//// C. PBR 렌더링 (노멀맵 사용)
	//VF_PBR = VF_STANDARD | VF_TANGENT | VF_BINORMAL,

	//// D. 스킨드 애니메이션 (Skinning)
	//VF_SKINNED = VF_STANDARD | VF_BONE_ID | VF_WEIGHT,

	//// E. 풀 스펙 스킨드 PBR 모델
	//VF_FULL_SKIN = VF_PBR | VF_BONE_ID | VF_WEIGHT,
#pragma endregion

	VF_MAX
};


float StrideFromFlag(VertexFlag Flag);

#pragma endregion
#pragma region Vertex_Structures
struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
	XMFLOAT2 TexCoord;
	XMFLOAT3 Normal;

	
	//XMFLOAT3 Tangent;
	//XMFLOAT3 BiNormal;
	//uint32_t BoneInidces[4];
	//XMFLOAT4 BoneWeights;
	//float padding;
};

#pragma endregion
#pragma region Topology
enum PRIMTYPE {
	PT_POINTLIST = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	PT_LINELIST = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	PT_LINESTRIP = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	PT_TRIANGLELIST = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	PT_TRIANGLESTRIP = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	//PT_TRIANGLEFAN = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLEFAN,
};
#pragma endregion

#pragma region helperfunc

template<typename T>
inline void SafeRelease(T*& ptr)
{
	if (ptr) { ptr->Release(); ptr = nullptr; }
}

template<typename T>
inline void SafeDelete(T*& ptr)
{
	delete ptr; ptr = nullptr;
}

DWORD AlignCBSize(DWORD size);
int CreateVertexBuffer(ID3D11Device* pDev, LPVOID pData, UINT size, ID3D11Buffer** ppVB);
int CreateConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB);
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB);
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, LPVOID pData, ID3D11Buffer** ppCB);
int CreateInputLayout(ID3D11Device* pDev, D3D11_INPUT_ELEMENT_DESC* ed, DWORD num, ID3DBlob* pVSCode, ID3D11InputLayout** ppLayout);
HRESULT UpdateDynamicBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, LPVOID pData, UINT size);




// 비트 OR 연산자 (조합)
inline constexpr VertexFlag operator|(VertexFlag a, VertexFlag b)
{
	return static_cast<VertexFlag>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

// 비트 AND 연산자 (포함 여부 확인)
inline constexpr VertexFlag operator&(VertexFlag a, VertexFlag b)
{
	return static_cast<VertexFlag>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

// 할당 연산자 (플래그 추가)
inline VertexFlag& operator|=(VertexFlag& a, VertexFlag b)
{
	a = a | b;
	return a;
}

// 예시: 노멀과 텍스처 좌표가 모두 필요하다면:
// VertexFlags flags = VertexFlags::VF_NORMAL | VertexFlags::VF_TEXCOORD; 

#pragma endregion

