#include "Cube.h"

Cube::Cube()
{
	mat = MaterialLibrary::CreateMaterial("cube_shader", "res/cube.shader");
	verts.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(-0.5f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(-0.5f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(-0.5f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) });
	verts.push_back({ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.5f) });
	// front face										 
	verts.push_back({ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.5f, 0.0f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.5f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.5f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.5f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.5f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.5f, 0.0f, 0.0f) });
	// left face										 
	verts.push_back({ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f) });
	verts.push_back({ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.5f, 0.0f) });
	// right face										 
	verts.push_back({ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f) });
	// bottom face										 
	verts.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f) });
	verts.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f) });
	// top face											 
	verts.push_back({ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f , 0.5f),  glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.5f, 0.5f) });
	verts.push_back({ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.5f, 0.0f) });
	verts.push_back({ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f) });
	verts.push_back({ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f) });

	for (int i = 0; i < 36; i++) {
		indicies.push_back(i);
	}

	mesh = new Mesh(verts, indicies);
}

Mesh * Cube::getMesh()
{
	return mesh;
}

Material * Cube::getMat()
{
	return mat;
}
