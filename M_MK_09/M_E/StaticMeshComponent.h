#pragma once
#include "RenderComponent.h"
#include <string>
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

