#pragma once


class Mesh;
class Material;


//Mesh & Material�� ���� ����. -> Mesh- > m_material index�� ���� material ������ ��� ����. 
// �ش� Ŭ������ ������Ʈ�� world matrix�� ������ ������ �ʿ��� ��� ������ ���� ����.
// StaticInstance�� ����� Instance�� �̸� ���� ������. -> ���� ���� �� ������?

class StaticModel
{


public:
	//ResourceManager -> staticMesh data ��ü�� ���� Mesh �� Material�� ����. -> 
	Mesh* mesh;
	Material* Material;




};
