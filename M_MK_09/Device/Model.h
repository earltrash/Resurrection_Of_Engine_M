#pragma once

//Mesh & Material를 갖고 있음. -> Mesh- > m_material index를 통해 material 정보를 들고 있음. 
// 해당 클래스는 오브젝트의 world matrix를 제외한 랜더에 필요한 모든 정보를 갖고 있음.
// StaticInstance의 멤버로 Instance와 이를 나눈 이유는. -> 굳이 없는 거 같은데?

#include "D3D11.h"
#include "DirectXCollision.h"

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
		std::vector<MeshPart> m_v_Parts;
		
		std::vector<DirectX::BoundingBox> m_v_Box;
	};

