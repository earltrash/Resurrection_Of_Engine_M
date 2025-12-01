#pragma once
#include "RenderComponent.h"
//얘는 ResourceManager나 mesh의 상위 혹은 하위 데이터를 운용해야 할듯?

//Engine과 Renderer 사이를 연결할 Component. dx의 인터페이스 구조체 (buffer같은 개념들을 wrapping해서 사용할 거임)
// Staticmesh data에 대한 관리와 운용 데이터의 수준에 따라서 이렇게 분류.


                               //여기까지 ResourceManager가 관리                                                           //그래서 얘는 하위 정보들에 접근해서 저~Model data를 설정  
// 순수한 정점  집합 및 버퍼   +Material(texture)                             +Mesh의 world 행렬 (월드에 그려지는 최종 값)                 //해당 컴포넌트는 StaticInstance를 갖고 있음.
//Vertex(the lowest) -> Mesh -> staticModel->          <이거 합칠까.>            StaticInstance                                         ->StaticMeshComponent


//ResourceManager //file 단위로 운용. 
//map
//Texrture // Model 


// 얘가 RenderComponent를 상속 받을거임.
// RenderComponent가 -> 
// ResourceManager는 필요한 자원에 따른, (의존성을 줄이기 위한), 하위 Maanger가 있음.

//해당 컴포넌트가 Update 될 일은 없지? 
//업데이트라고 한다면 상수버퍼나 shader 쪽이니깐. 
//Object 단위에서의 업데이트 되는 상수버퍼 자체는 월드 행렬 밖에 없을 거 같은데, 


class Model;

class StaticMeshComponent : public RenderComponent
{
public:
    StaticMeshComponent() = default;
    ~StaticMeshComponent() = default;
public:
    //받긴 하는데, 뭐 없긴 할듯 
    virtual void Update(float dTime);
    virtual void FixedUpdate(float dTime); //-> 유기 예정 
    //렌더 단계에서. 갖고 있는 Model 정보를 Renderer에게 넘겨주는 
    virtual void Render();

    void SetModel(std::string Path);
    Model* GetModel();
private:
    //그려야 하는 model의 pointer를 갖고 있어서, render 할 때 pointer만 줍소 하면 줄 걸 
    Model* m_p_model;
    
};

