#pragma once

using Microsoft::WRL::ComPtr;
using namespace DirectX;

#include <d3dcompiler.h> 
#pragma comment(lib, "D3DCompiler.lib")

#pragma region exception

class com_exception : public std::exception
{
public:
	com_exception(HRESULT hr) : result(hr) {}

	const char* what() const noexcept override
	{
		static char s_str[64] = {};
		sprintf_s(s_str, "Failure with HRESULT of %08X",
			static_cast<unsigned int>(result));
		return s_str;
	}

private:
	HRESULT result;
};

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

inline std::wstring ToWString(const std::string& s)
{
	std::wstring wsTmp(s.begin(), s.end());
	return wsTmp;
}


DWORD AlignCBSize(DWORD size);
int CreateVertexBuffer(ID3D11Device* pDev, LPVOID pData, UINT size, ID3D11Buffer** ppVB);
int CreateConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB);
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB);
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, LPVOID pData, ID3D11Buffer** ppCB);
int CreateInputLayout(ID3D11Device* pDev, D3D11_INPUT_ELEMENT_DESC* ed, DWORD num, ID3DBlob* pVSCode, ID3D11InputLayout** ppLayout);
HRESULT UpdateDynamicBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, LPVOID pData, UINT size);
HRESULT ShaderCompile(const WCHAR* FileName, const  char* EntryPoint, const char* ShaderModel, ID3DBlob** code);
void HR_T(HRESULT hr);
ID3D11ShaderResourceView* CreateTexture(std::wstring path, ID3D11Device* device);

#pragma endregion

