#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies)
{
	VBO = new VertexBuffer(nullptr, 0);
	IBO = new IndexBuffer(nullptr, 0);


	m_Indicies = indicies;
	m_Verticies = verticies;

	VBO->Unbind();
	IBO->Unbind();

	VAO.Bind();
	VBO->Bind();
	VBO->SetData(m_Verticies.data(), m_Verticies.size() * sizeof(Vertex));
	m_layout.Push<float>(3);
	m_layout.Push<float>(3);
	VAO.AddBuffer(*VBO, m_layout);
	IBO->Bind();
	IBO->SetData(m_Indicies.data(), m_Indicies.size() * sizeof(unsigned int));
}
