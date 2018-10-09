#include "Chunk.h"

Chunk::Chunk(sf::Vector2i position, int size, Material* mat)
{
	this->position = position;
	this->mat = mat;
	this->chunkSize = size;

	unsigned int iteration = 0;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			verts.push_back({
				glm::vec3(x + position.x, 0, y + position.y),
				glm::vec3(x + position.x, 0, y + position.y)
			});

			indicies.push_back(iteration);
			iteration++;
		}
	}

	mesh = new Mesh(verts, indicies);
}

Chunk::~Chunk()
{
	delete mesh;
	// delete mat;
}

void Chunk::Update(int seed, int noiseType, float amplitude)
{
	if (this->seed != seed || this->noiseType != noiseType || this->amplitude != amplitude) 
	{
		this->seed = seed;
		this->noiseType = noiseType;
		this->amplitude = amplitude;

		noise.SetNoiseType(static_cast<FastNoise::NoiseType>(noiseType));
		noise.SetSeed(seed);
		verts.clear();
		indicies.clear();
		unsigned int iteration = 0;
		for (int y = 0; y < chunkSize; y++) {
			for (int x = 0; x < chunkSize; x++) {
				double z = noise.GetNoise(x + position.x, y + position.y);
				verts.push_back({
					glm::vec3(x + position.x, std::floor(z * amplitude), y + position.y),
					glm::vec3(x + position.x, std::floor(z * amplitude), y + position.y)
				});
			}
		}

		mesh->VBO->SetData(verts.data(), verts.size() * sizeof(Vertex));
	}
}

Mesh * Chunk::getMesh()
{
	return mesh;
}

Material * Chunk::getMat()
{
	return mat;
}

sf::Vector2i Chunk::getChunkPos()
{
	return position / chunkSize;
}
