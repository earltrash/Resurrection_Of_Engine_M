#pragma once
// ��� 
// Assimp�� ���ؼ� FBX�Ľ�
// 
// ResourceData Model, Material, Sound?, ETC  
// ������ ���Ŀ� ����? ����� ������, Device-> device or context�� �ްų� �� �� ����(DX�� Singleton�� ������ �� ����)

//FileLoader�� �ر��� .

//#include "Commons.h" //commons -> helper �Լ���, pch�� �и�
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
	void ModelLoad(std::string filepath, ModelType Type); //ĸ��ȭ? �ܺο��� ModelType�� �˾ƾ� �ϴ°� �� ��ġ�� �ϳ�, �� boolean���� ������ ������� ������. 



	
public:
	void Set_Up(RM_Set Set); //-> Device, context�� �����ް�. MeshResource�� resource���� device ��ü�� �길 ����
	ComPtr<ID3D11Device> GetDevice();
	ComPtr<ID3D11DeviceContext>GetDeviceContext();

private:
	ComPtr<ID3D11Device> m_pDevice = nullptr;
	ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;

private:
	std::unique_ptr<MeshResource> m_MeshResource;
};

