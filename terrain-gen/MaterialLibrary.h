#pragma once
#include <map>
#include "Material.h"

class MaterialLibrary
{
public:

	/// <summary>
	/// Gets a pointer to a material given its id
	/// </summary>
	/// <param name="id">The material identifier.</param>
	/// <returns>material pointer</returns>
	static Material* GetMaterial(std::string id);

	/// <summary>
	/// Creates a material given a shader and id.
	/// </summary>
	/// <param name="id">The material identifier.</param>
	/// <param name="shaderPath">The shader path.</param>
	/// <returns></returns>
	static Material* CreateMaterial(const std::string id, const std::string shaderPath);

	static std::map<std::string, Material*> m_Materials;
private:
	MaterialLibrary() {};
};