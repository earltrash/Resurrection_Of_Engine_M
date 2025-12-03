#pragma once
#include "Singleton.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"

#include <wrl/client.h>

class SoundResource; 
class TextureResource;
class ShaderResource;


struct RM_Set
{
	Microsoft::WRL::ComPtr<ID3D11Device> Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
};


class ResourceManager :public Singleton<ResourceManager>
{

friend class Singleton<ResourceManager>;

private:
	ResourceManager() = default;
	~ResourceManager() = default;


public:
	void ModelLoad(std::string& filepath, ModelType Type); //캡슐화? 외부에서 ModelType을 알아야 하는게 좀 골치긴 하네, 뭐 boolean으로 나눠도 상관없지 않을까. 
public:
	void Set_Up(RM_Set Set); //-> Device, context를 제공받고. MeshResource가 resource만들 device 자체는 얘만 들자
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>GetDeviceContext();
	ShaderResource* GetShaderResource();
	ModelResource* GetModelResource();
	TextureResource* GetTextureResource();

private:

	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;
private:

	// Sound 는 너무 먼 미래야~ 
	std::unique_ptr <ModelResource> m_MeshResource;
	std::unique_ptr <ShaderResource> m_ShaderResource;
	std::unique_ptr <TextureResource> m_TextureResource;

	
};

