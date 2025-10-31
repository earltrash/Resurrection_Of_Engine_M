#pragma once

//Mesh & Material�� ���� ����. -> Mesh- > m_material index�� ���� material ������ ��� ����. 
// �ش� Ŭ������ ������Ʈ�� world matrix�� ������ ������ �ʿ��� ��� ������ ���� ����.
// StaticInstance�� ����� Instance�� �̸� ���� ������. -> ���� ���� �� ������?

#include "Mesh.h"
#include <vector>

class Material;

class Model
{
	friend class MeshResource;
	friend class DX_Renderer;

public:
	Model() = default;
	~Model() = default;

	void Render(ID3D11DeviceContext* DX);

private:
	Mesh* m_Mesh; //-> ������ FBX�� ���� Mesh�� �ִ� texture������ ������ ����.
	Material* m_Material = nullptr;

	//Material�� ���� ������ ���
	//Node�� �ٷ�ٸ� ���⼭ �߰��� ����. -> flag�� ���ؼ� Model data�� �а� Render�� ���� �ش� ������ ���� ���ؼ� flagó�� �� ��?



};


//Model�� Mesh�� Material(Texture)�� ���� ����. 
//Mesh�� �Һ��� ������ �±� �ѵ�, Material�� ������� �ʴ� �̻� ��� ����°� �±���. 
//Renderpass���� 