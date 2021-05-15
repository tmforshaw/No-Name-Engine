#include "World.hpp"

Chunk World::m_chunks[CHUNKS_Y][CHUNKS_Z][CHUNKS_X] = {};

void World::Init()
{
	for ( unsigned short y = 0; y < CHUNKS_Y; y++ )			// Iterate Y
		for ( unsigned short z = 0; z < CHUNKS_Z; z++ )		// Iterate Z
			for ( unsigned short x = 0; x < CHUNKS_X; x++ ) // Iterate X
			{
				m_chunks[y][z][x] = Chunk( x, y, z );

				// std::cout << "Initialised" << std::endl;
			}
}

void World::DrawChunks( const VertexArray& p_VAO, const ShaderProgram& shader )
{
	for ( unsigned short y = 0; y < CHUNKS_Y; y++ )			// Iterate Y
		for ( unsigned short z = 0; z < CHUNKS_Z; z++ )		// Iterate Z
			for ( unsigned short x = 0; x < CHUNKS_X; x++ ) // Iterate X
			{
				m_chunks[y][z][x].DrawMesh( p_VAO, shader );
			}
}

void World::PushChunkVertices( std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices )
{
	for ( unsigned short y = 0; y < CHUNKS_Y; y++ )			// Iterate Y
		for ( unsigned short z = 0; z < CHUNKS_Z; z++ )		// Iterate Z
			for ( unsigned short x = 0; x < CHUNKS_X; x++ ) // Iterate X
			{
				m_chunks[y][z][x].PushVertices( p_vertices, p_indices );
			}
}