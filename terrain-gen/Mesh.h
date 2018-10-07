#pragma once
#include "Material.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Buffer.h"
#include "GLUtil.h"
#include <vector>

/// <summary>
/// Vertex struct
/// </summary>
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Mesh
{
public:
	VertexArray VAO;
	Buffer* IBO;
	Buffer* VBO;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Mesh"/> class.
	/// </summary>
	/// <param name="verticies">The verticies of the mesh.</param>
	/// <param name="indicies">The indicies of the mesh.</param>
	Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies);

	/// <summary>
	/// Initializes a new empty instance of the <see cref="Mesh"/> class.
	/// </summary>
	Mesh() {
		VBO = new VertexBuffer(nullptr, 0);
		IBO = new IndexBuffer(nullptr, 0);
	};
protected:
	std::vector<Vertex> m_Verticies;
	std::vector<unsigned int> m_Indicies;
	BufferLayout m_layout;

};