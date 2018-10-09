#pragma once
#include <vector>
#include "FastNoise.h"
#include "Mesh.h"
#include "MaterialLibrary.h"

class Chunk {
public:
	Chunk(sf::Vector2i position, int size, Material* mat);
	~Chunk();
	void Update(int seed, int noiseType, float amplitude);
	Mesh* getMesh();
	Material* getMat();
	sf::Vector2i getChunkPos();
	sf::Vector2i position;

private:
	FastNoise noise;
	std::vector<Vertex> verts;
	std::vector<unsigned int> indicies;
	Mesh* mesh;
	Material* mat;

	int seed, noiseType, chunkSize;
	float amplitude;
};