#pragma once

//Mesh & Material를 갖고 있음. -> Mesh- > m_material index를 통해 material 정보를 들고 있음. 
// 해당 클래스는 오브젝트의 world matrix를 제외한 랜더에 필요한 모든 정보를 갖고 있음.
// StaticInstance의 멤버로 Instance와 이를 나눈 이유는. -> 굳이 없는 거 같은데?

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
	Mesh* m_Mesh; //-> 어차피 FBX를 통해 Mesh에 있는 texture정보를 보유할 거임.
	Material* m_Material = nullptr;

	//Material에 대한 정보는 고민
	//Node를 다룬다면 여기서 추가될 예정. -> flag를 통해서 Model data를 읽고 Render될 때도 해당 변수의 값을 통해서 flag처리 할 듯?



};


//Model은 Mesh랑 Material(Texture)을 갖고 있음. 
//Mesh는 불변의 개념이 맞긴 한데, Material은 변경되지 않는 이상 계속 들고가는게 맞긴함. 
//Renderpass에서 