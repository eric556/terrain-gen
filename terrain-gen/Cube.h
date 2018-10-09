#pragma once
#include "Mesh.h"
#include "MaterialLibrary.h"

class Cube {
public:
	Cube();
	Mesh* getMesh();
	Material* getMat();
private:
	Mesh* mesh;
	Material* mat;
	std::vector<Vertex> verts;
	std::vector<unsigned int> indicies;

};