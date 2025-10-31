#pragma once
#include "RenderComponent.h"
#include "Model.h"

//��� ResourceManager�� mesh�� ���� Ȥ�� ���� �����͸� ����ؾ� �ҵ�?

//Engine�� Renderer ���̸� ������ Component. dx�� �������̽� ����ü (buffer���� ������� wrapping�ؼ� ����� ����)
// Staticmesh data�� ���� ������ ��� �������� ���ؿ� ���� �̷��� �з�.


                               //������� ResourceManager�� ����                                                           //�׷��� ��� ���� �����鿡 �����ؼ� ��~Model data�� ����  
// ������ ����  ���� �� ����   +Material(texture)                             +Mesh�� world ��� (���忡 �׷����� ���� ��)                 //�ش� ������Ʈ�� StaticInstance�� ���� ����.
//Vertex(the lowest) -> Mesh -> staticModel->          <�̰� ��ĥ��.>            StaticInstance                                         ->StaticMeshComponent


//ResourceManager //file ������ ���. 
//map
//Texrture // Model 


// �갡 RenderComponent�� ��� ��������.
// RenderComponent�� -> 
// ResourceManager�� �ʿ��� �ڿ��� ����, (�������� ���̱� ����), ���� Maanger�� ����.

//�ش� ������Ʈ�� Update �� ���� ����? 
//������Ʈ��� �Ѵٸ� ������۳� shader ���̴ϱ�. 

class StaticMeshComponent : public RenderComponent
{
public:
    StaticMeshComponent() = default;
    ~StaticMeshComponent() = default;
public:
    virtual void Update() {}
    virtual void FixedUpdate(float dt) {}


    //���� �ܰ迡��. ���� �ִ� Model ������ Renderer���� �Ѱ��ִ� 
    virtual void Render();


private:
    std::unique_ptr<Model> m_Model;
    
};

