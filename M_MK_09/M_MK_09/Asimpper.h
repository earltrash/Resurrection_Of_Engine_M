#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Commons.h" //by Device , DX
#include "Model.h"


class Asimpper
{
private:

	Assimp::Importer m_Importer;
    ID3D11Device* m_Device = nullptr;
    ID3D11DeviceContext* m_DXDC = nullptr;

public:
    void Initalize(ID3D11Device* DV, ID3D11DeviceContext* DC) { SetDevices(DV, DC); }
    void SetDevices(ID3D11Device* DV, ID3D11DeviceContext* DC) { m_Device = DV; m_DXDC = DC; }
    std::vector<Model*> m_Models;
    bool LoadModel(const std::string& filePath, ID3D11Device* device);
private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    Model* ProcessModel(aiMesh* mesh, const aiScene* scene);
    
};

