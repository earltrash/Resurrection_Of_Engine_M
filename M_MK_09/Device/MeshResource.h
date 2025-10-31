#pragma once

//Mesh�� �����ϴ� 

#include "Model.h"
#include <string>

//���� ������
// 
// Ȯ���ڸ� ������ �̸����� �����ϰų� �ϴ� ��? �ϴ� �⺻���� ���·θ� �غ���.
// 
//1. Resource Manager�� ���� MeshResource�� �Ľ� �� ���� (��Ȯ���� 3DModeldata�� �ڷᱸ���� ����
//2. Texture�� Material�� �𸣰ڴ�. 
//3. StaticMeshComponent�� dynamicMeshComponent�� 3d Instance�� ���� 3d Model�� �����͸� ���⼭ �޾ƿ�. 
//
// Resorce�� �׷����� Instance�� �и��ϴ� ���� 
//
// Model�� ���� material�� �ּҳ� �������� �ѱ� ���� �ִ�. -> �׷� ���� �ٸ� ������ Matrial�� �����ؾ� �ұ�. 
// ��Ȯ���� material�� ��θ� ������ �ΰ�, �ʿ��� ��, texture ������ ������ ������ �������� ���� ������. 
//
//
//

enum class ModelType
{
	Static,
	Skeleton
};



class MeshResource
{
public:
	MeshResource() = default;
	~MeshResource() = default;

public:

	void LoadFile(std::string FilePath , ModelType Type ); //ResourceManager�� ���ؼ� ȣ��Ǵ� �Լ�.
	std::unordered_map<std::string, Model> m_Modelmap;


};

