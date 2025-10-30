#pragma once
#include "Component.h"


//Engine과 Renderer 사이를 연결할 Component. dx의 인터페이스 구조체 (buffer같은 개념들을 wrapping해서 사용할 거임)
// Staticmesh data에 대한 관리와 운용 데이터의 수준에 따라서 이렇게 분류.


                               //여기까지 ResourceManager가 관리                                                           //그래서 얘는 하위 정보들에 접근해서 저~Model data를 설정  
// 순수한 정점  집합 및 버퍼   +Material(texture)                  +Mesh의 world 행렬 (월드에 그려지는 최종 값)                 //해당 컴포넌트는 StaticInstance를 갖고 있음.
//Vertex(the lowest) -> Mesh -> staticModel->                        StaticInstance                                         ->StaticMeshComponent


//ResourceManager //file 단위로 운용. 
//map
//Texrture // Model 



// ResourceManager는 필요한 자원에 따른, (의존성을 줄이기 위한), 하위 Maanger가 있음.

class StaticMeshComponent : public Component
{
    






};

