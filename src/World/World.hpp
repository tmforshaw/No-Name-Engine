#pragma once
#include "Chunk.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CHUNKS_X 10
#define CHUNKS_Y 1
#define CHUNKS_Z 10

class World
{
private:
	Chunk chunks[CHUNKS_Y][CHUNKS_Z][CHUNKS_X];

public:
	World();

	Chunk GetChunk( unsigned short i, unsigned short j, unsigned short k ) const;

	void DrawChunks( VertexBufferObject* VBO ) const;
	void GenerateChunkMesh( unsigned int i, unsigned int j, unsigned int k );
	void GenerateChunkMeshes( glm::vec3 position );
};

extern World world;