#pragma once
#include "Component.h"


//Engine�� Renderer ���̸� ������ Component. dx�� �������̽� ����ü (buffer���� ������� wrapping�ؼ� ����� ����)
// Staticmesh data�� ���� ������ ��� �������� ���ؿ� ���� �̷��� �з�.


                               //������� ResourceManager�� ����                                                           //�׷��� ��� ���� �����鿡 �����ؼ� ��~Model data�� ����  
// ������ ����  ���� �� ����   +Material(texture)                  +Mesh�� world ��� (���忡 �׷����� ���� ��)                 //�ش� ������Ʈ�� StaticInstance�� ���� ����.
//Vertex(the lowest) -> Mesh -> staticModel->                        StaticInstance                                         ->StaticMeshComponent


//ResourceManager //file ������ ���. 
//map
//Texrture // Model 



// ResourceManager�� �ʿ��� �ڿ��� ����, (�������� ���̱� ����), ���� Maanger�� ����.

class StaticMeshComponent : public Component
{
    






};

