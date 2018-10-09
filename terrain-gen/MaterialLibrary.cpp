#include "MaterialLibrary.h"

std::map<std::string, Material*> MaterialLibrary::m_Materials = {};

Material * MaterialLibrary::GetMaterial(std::string id)
{
	return m_Materials[id];
}

Material * MaterialLibrary::CreateMaterial(const std::string id, const std::string shaderPath)
{
	if (m_Materials[id] != nullptr) {
		return m_Materials[id];
	}
	else 
	{
		m_Materials[id] = new Material(shaderPath);
		return m_Materials[id];
	}
}
