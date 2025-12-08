#pragma once
#include "Model.h"
#include <string>
#include <unordered_map>

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
	int LoadFile(std::string FilePath , ModelType Type ); 
	Model* GetModel(std::string Key);
private:

	std::unordered_map<std::string, std::unique_ptr<Model>> m_Modelmap;
};

