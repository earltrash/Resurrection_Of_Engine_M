#pragma once
// 기능 
// Assimp를 통해서 FBX파싱
// 
// ResourceData Model, Material, Sound?, ETC  
// 데이터 형식에 따라서? 멤버로 나누고, Device-> device or context를 받거나 할 수 있음(DX의 Singleton을 억제할 수 있음)

//FileLoader는 밑까지 .

//#include "Commons.h" //commons -> helper 함수로, pch랑 분리
#include "Singleton.h"
#include "MeshResource.h"

using namespace std;


class SoundResource;
class MaterialResource;


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
	void ModelLoad(std::string filepath, ModelType Type); //캡슐화? 외부에서 ModelType을 알아야 하는게 좀 골치긴 하네, 뭐 boolean으로 나눠도 상관없지 않을까. 



	
public:
	void Set_Up(RM_Set Set); //-> Device, context를 제공받고. MeshResource가 resource만들 device 자체는 얘만 들자
	ComPtr<ID3D11Device> GetDevice();
	ComPtr<ID3D11DeviceContext>GetDeviceContext();

private:
	ComPtr<ID3D11Device> m_pDevice = nullptr;
	ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;

private:
	std::unique_ptr<MeshResource> m_MeshResource;
};

