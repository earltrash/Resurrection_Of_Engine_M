#pragma once
#include "Component.h"

//��� ResourceManager�� mesh�� ���� Ȥ�� ���� �����͸� ����ؾ� �ҵ�?

//Engine�� Renderer ���̸� ������ Component. dx�� �������̽� ����ü (buffer���� ������� wrapping�ؼ� ����� ����)
// Staticmesh data�� ���� ������ ��� �������� ���ؿ� ���� �̷��� �з�.


                               //������� ResourceManager�� ����                                                           //�׷��� ��� ���� �����鿡 �����ؼ� ��~Model data�� ����  
// ������ ����  ���� �� ����   +Material(texture)                             +Mesh�� world ��� (���忡 �׷����� ���� ��)                 //�ش� ������Ʈ�� StaticInstance�� ���� ����.
//Vertex(the lowest) -> Mesh -> staticModel->          <�̰� ��ĥ��.>            StaticInstance                                         ->StaticMeshComponent


//ResourceManager //file ������ ���. 
//map
//Texrture // Model 



// ResourceManager�� �ʿ��� �ڿ��� ����, (�������� ���̱� ����), ���� Maanger�� ����.

class StaticMeshComponent : public Component
{
    






};

