#include "Material.h"

Material::Material(const std::string path)
{
	std::ifstream stream(path);

	std::stringstream ss[2];
	std::string line;
	int type = -1;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = 0;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = 1;
			}
		}
		else
		{
			ss[type] << line << "\n";
		}
	}

	if (!m_Shader.loadFromMemory(ss[0].str(), ss[1].str()))
	{
		std::cout << "Could not load shader: " << path << "\n";
	}
}

void Material::Bind()
{
	sf::Shader::bind(&m_Shader);
	for (auto const& mat : m_Mat4Uniforms)
	{
		m_Shader.setUniform(mat.first, sf::Glsl::Mat4(&mat.second[0][0]));
	}

	for (auto const& vec : m_Vec3Uniforms)
	{
		m_Shader.setUniform(vec.first, sf::Glsl::Vec3(vec.second.x, vec.second.y, vec.second.z));
	}

	for (auto const& unit : m_activeTextures)
	{
		int unitID = unit.first;
		std::string uniform = unit.second;
		m_Shader.setUniform(uniform, unitID);
		GLCall(glActiveTexture(GL_TEXTURE0 + unitID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureUniforms[uniform]->getNativeHandle()));
	}

	for (auto const& i : m_IntUniforms)
	{
		m_Shader.setUniform(i.first, i.second);
	}

	for (auto const& f : m_FloatUniforms)
	{
		m_Shader.setUniform(f.first, f.second);
	}
}

void Material::SetUniform(std::string id, int unit, sf::Texture* texture)
{
	m_TextureUniforms[id] = texture;
	m_activeTextures[unit] = id;
}

void Material::SetUniform(std::string id, glm::vec3 vec)
{
	m_Vec3Uniforms[id] = vec;
}

void Material::SetUniform(std::string id, glm::mat4 mat)
{
	m_Mat4Uniforms[id] = mat;
}

void Material::SetUniform(std::string id, float num)
{
	m_FloatUniforms[id] = num;
}

void Material::SetUniform(std::string id, glm::vec3 vecs[], int size)
{
	for (int i = 0; i < size; i++)
	{
		m_Vec3Uniforms[id + "[" + std::to_string(i) + "]"] = vecs[i];
	}
}

void Material::SetUniform(std::string id, int i)
{
	m_IntUniforms[id] = i;
}
