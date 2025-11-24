#pragma once

//Mesh를 포함하는 

#include <string>
#include "Model.h"


enum class ModelType
{
	Static,
	Skeleton
};

class ModelResource
{
public:
	ModelResource() = default;
	~ModelResource() = default;

public:

	void LoadFile(std::string FilePath , ModelType Type ); 
	Model* GetModel(std::string Key);
private:

	std::unordered_map<std::string, unique_ptr<Model>> m_Modelmap;
};

