#include "World.hpp"

World world( 0 ); // I don't like this solution

void InitWorld( unsigned int seed )
{
	// Instantiate a world
	world = World( seed );
}

World::World( unsigned int seed )
{
	// Instantiate chunks
	for ( unsigned short i = 0; i < CHUNKS_Y; i++ )			// Iterate Y
		for ( unsigned short j = 0; j < CHUNKS_Z; j++ )		// Iterate Z
			for ( unsigned short k = 0; k < CHUNKS_X; k++ ) // Iterate X
				chunks[i][j][k] = Chunk( i, j, k );

	// Seed the random function
	srand( seed );

	// Generate perlin noise
	PerlinNoise2D( rand(), 7, noise, 0.05f );
}

Chunk World::GetChunk( unsigned short i, unsigned short j, unsigned short k ) const
{
	return chunks[i][j][k];
}

float World::GetNoise( unsigned short j, unsigned short k )
{
	return noise[j][k];
}

void World::DrawChunks( VertexBufferObject* VBO )
{
	for ( unsigned short i = 0; i < CHUNKS_Y; i++ )			// Iterate Y
		for ( unsigned short j = 0; j < CHUNKS_Z; j++ )		// Iterate Z
			for ( unsigned short k = 0; k < CHUNKS_X; k++ ) // Iterate X
				chunks[i][j][k].DrawMesh( VBO );
}

void World::GenerateChunkMesh( unsigned int i, unsigned int j, unsigned int k, TextureAtlas texSheet )
{
	chunks[i][j][k].GenerateMesh( texSheet );
}

void World::GenerateChunkMeshes( glm::vec3 position, TextureAtlas texSheet )
{
	// Eventually this will be a better algorithm that generates depending on position

	for ( unsigned short i = 0; i < CHUNKS_Y; i++ )			// Iterate Y
		for ( unsigned short j = 0; j < CHUNKS_Z; j++ )		// Iterate Z
			for ( unsigned short k = 0; k < CHUNKS_X; k++ ) // Iterate X
				if ( !chunks[i][j][k].IsGenerated() )		// Not generated yet
				{
					GenerateChunkMesh( i, j, k, texSheet );
					return; // Stop generating until next loop
				}
}
