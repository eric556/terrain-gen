#pragma once
#include <GL\glew.h>
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>
#include <SFML\Graphics.hpp>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLUtil.h"

class Material
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Material"/> class
	/// given a path to a shader
	/// </summary>
	/// <param name="path">The path to a shader.</param>
	Material(const std::string path);

	/// <summary>
	/// Binds the internal shader and sets the uniforms specified in the maps.
	/// </summary>
	void Bind();

	/// <summary>
	/// Sets a sampler uniform to the given texture unit and 
	/// attaches the given texture pointer to the texture unit
	/// </summary>
	/// <param name="id">The uniform identifier.</param>
	/// <param name="unit">The texture unit.</param>
	/// <param name="texture">The texture pointer.</param>
	void SetUniform(std::string id, int unit, sf::Texture * texture);

	/// <summary>
	/// Sets a vec3 uniform
	/// </summary>
	/// <param name="id">The uniform identifier.</param>
	/// <param name="vec">The vec.</param>
	void SetUniform(std::string id, glm::vec3 vec);

	/// <summary>
	/// Sets a mat4 uniform
	/// </summary>
	/// <param name="id">The uniform identifier.</param>
	/// <param name="mat">The mat.</param>
	void SetUniform(std::string id, glm::mat4 mat);

	/// <summary>
	/// Sets a float uniform
	/// </summary>
	/// <param name="id">The uniform identifier.</param>
	/// <param name="num">The number.</param>
	void SetUniform(std::string id, float num);

	/// <summary>
	/// Sets a vec3 array uniform
	/// </summary>
	/// <param name="id">The uidentifier.</param>
	/// <param name="vecs">The vecs.</param>
	/// <param name="size">The size.</param>
	void SetUniform(std::string id, glm::vec3 vecs[], int size);

	/// <summary>
	/// Sets an int uniform
	/// </summary>
	/// <param name="id">The uniform identifier.</param>
	/// <param name="i">The int.</param>
	void SetUniform(std::string id, int i);
private:
	sf::Shader m_Shader;
	std::map < std::string, sf::Texture*> m_TextureUniforms;
	std::map < int, std::string> m_activeTextures;
	std::map <std::string, glm::vec3> m_Vec3Uniforms;
	std::map <std::string, glm::mat4> m_Mat4Uniforms;
	std::map <std::string, float> m_FloatUniforms;
	std::map <std::string, int> m_IntUniforms;
};