#pragma once
#include "../Noise/PerlinNoise.hpp"
#include "../Textures/Textures.hpp"
#include "Chunk.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CHUNKS_X 20
#define CHUNKS_Y 1
#define CHUNKS_Z 20

class World
{
private:
	Chunk chunks[CHUNKS_Y][CHUNKS_Z][CHUNKS_X];
	float noise[NOISE_SIZE_Y][NOISE_SIZE_X];

public:
	World( unsigned int seed );

	Chunk GetChunk( unsigned short i, unsigned short j, unsigned short k ) const;
	float GetNoise( unsigned short j, unsigned short k );

	void DrawChunks( VertexBufferObject* VBO );
	void GenerateChunkMesh( unsigned int i, unsigned int j, unsigned int k, TextureAtlas texSheet );
	void GenerateChunkMeshes( glm::vec3 position, TextureAtlas texSheet );
};

extern World world;

void InitWorld( unsigned int seed );