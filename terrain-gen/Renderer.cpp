#include "Renderer.h"

void Renderer::Clear(sf::Vector3f color)
{
	GLCall(glClearColor(color.x, color.y, color.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(VertexArray * VAO, Buffer * IBO, Material * mat)
{
	VAO->Bind();
	IBO->Bind();
	mat->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(Mesh * mesh, Material * mat)
{
	Renderer::Draw(mesh, mat, GL_TRIANGLES);
}


void Renderer::Draw(Mesh * mesh, Material * mat, GLenum drawMethod)
{
	mesh->VAO.Bind();
	mesh->IBO->Bind();
	if (mat)
	{
		mat->Bind();
	}
	GLCall(glDrawElements(drawMethod, mesh->IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
}