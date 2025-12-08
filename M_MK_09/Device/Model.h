#pragma once

//Mesh & Material를 갖고 있음. -> Mesh- > m_material index를 통해 material 정보를 들고 있음. 
// 해당 클래스는 오브젝트의 world matrix를 제외한 랜더에 필요한 모든 정보를 갖고 있음.
// StaticInstance의 멤버로 Instance와 이를 나눈 이유는. -> 굳이 없는 거 같은데?

class Material;
class Mesh;

struct MeshPart 
{
	std::shared_ptr<Mesh> mesh;

	std::shared_ptr<Material> material; 
};

	class Model
	{
		friend class ModelResource;
		friend class DX_Renderer;


	public:
		Model() = default;
		~Model() = default;
	public:
		void Render(ID3D11DeviceContext* DX);

	private:
		std::vector<MeshPart> m_Parts;

	};


//Model은 Mesh랑 Material(Texture)을 갖고 있음. 
//Mesh는 불변의 개념이 맞긴 한데, Material은 변경되지 않는 이상 계속 들고가는게 맞긴함. 
//Renderpass에서 