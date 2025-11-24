#pragma once
// 기능 
// Assimp를 통해서 FBX파싱
// 
// ResourceData Model, Material, Sound?, ETC  
// 데이터 형식에 따라서? 멤버로 나누고, Device-> device or context를 받거나 할 수 있음(DX의 Singleton을 억제할 수 있음)

//FileLoader는 밑까지 .

#include "Singleton.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"
using namespace std;


class SoundResource; //얘는 그냥 엔진 단에서 Sound
class TextureResource;
class ShaderResource;
//class MaterialResource;

//Device


struct RM_Set
{
	ComPtr<ID3D11Device> Device = nullptr;
	ComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
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
	ComPtr<ID3D11Device> GetDevice();
	ComPtr<ID3D11DeviceContext>GetDeviceContext();
	ShaderResource* GetShaderResource();
	ModelResource* GetModelResource();
	TextureResource* GetTextureResource();
private:
	ComPtr<ID3D11Device> m_pDevice = nullptr;
	ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;

private:
	// TO DO MODEL_Resource
	// Material - material cb & Texture 
	// Sound 는 너무 먼 미래야~ 
	std::unique_ptr <ModelResource> m_MeshResource;
	std::unique_ptr <ShaderResource> m_ShaderResource; //Shader 객체를 Vec으로 보관 -> 후, Flag(iNDEX)
	//모든 texture가 material이랑 엮일 일은 없다고 생각해.
	std::unique_ptr <TextureResource> m_TextureResource;

	//그래서 분리하고, material은 fbx를 통해서 읽어 올거야.  -> 그냥 mesh에서 읽으면 되는 거잖아 
	//std::unique_ptr <MaterialResource> m_MaterialResource;
	// Phong Model이니, Material이 가져야 할 값은 Difffuse Specular Ambient Texture Name ? 
};

