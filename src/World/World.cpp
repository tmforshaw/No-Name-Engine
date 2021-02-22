#include "World.hpp"

// Instantiate a world
World world = World();

World::World()
{
	// Instantiate chunks
	for ( unsigned short i = 0; i < CHUNKS_Y; i++ )			// Iterate Y
		for ( unsigned short j = 0; j < CHUNKS_Z; j++ )		// Iterate Z
			for ( unsigned short k = 0; k < CHUNKS_X; k++ ) // Iterate X
				chunks[i][j][k] = Chunk( i, j, k );
}

Chunk World::GetChunk( unsigned short i, unsigned short j, unsigned short k ) const
{
	return chunks[i][j][k];
}
void World::DrawChunks( VertexBufferObject* VBO ) const
{
	for ( unsigned short i = 0; i < CHUNKS_Y; i++ )			// Iterate Y
		for ( unsigned short j = 0; j < CHUNKS_Z; j++ )		// Iterate Z
			for ( unsigned short k = 0; k < CHUNKS_X; k++ ) // Iterate X
				chunks[i][j][k].DrawMesh( VBO );
}

void World::GenerateChunkMesh( unsigned int i, unsigned int j, unsigned int k )
{
	chunks[i][j][k].GenerateMesh();
}

void World::GenerateChunkMeshes( glm::vec3 position )
{
	// Eventually this will be a better algorithm that generates depending on position

	for ( unsigned short i = 0; i < CHUNKS_Y; i++ )			// Iterate Y
		for ( unsigned short j = 0; j < CHUNKS_Z; j++ )		// Iterate Z
			for ( unsigned short k = 0; k < CHUNKS_X; k++ ) // Iterate X
				GenerateChunkMesh( i, j, k );
}
