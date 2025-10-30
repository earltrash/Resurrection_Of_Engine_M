#pragma once


class Mesh;
class Material;


//Mesh & Material를 갖고 있음. -> Mesh- > m_material index를 통해 material 정보를 들고 있음. 
// 해당 클래스는 오브젝트의 world matrix를 제외한 랜더에 필요한 모든 정보를 갖고 있음.
// StaticInstance의 멤버로 Instance와 이를 나눈 이유는. -> 굳이 없는 거 같은데?

class StaticModel
{


public:
	//ResourceManager -> staticMesh data 객체를 통해 Mesh 및 Material을 받음. -> 
	Mesh* mesh;
	Material* Material;




};
