#include "World.hpp"

World::World()
{
	for ( unsigned short i = 0; i < sizeof( chunks ) / sizeof( chunks[0] ); i++ )					  // Iterate Y
		for ( unsigned short j = 0; j < sizeof( chunks[0] ) / sizeof( chunks[0][0] ); j++ )			  // Iterate Z
			for ( unsigned short k = 0; k < sizeof( chunks[0][0] ) / sizeof( chunks[0][0][0] ); k++ ) // Iterate X
				chunks[i][j][k] = Chunk( i, j, k );
}

void World::DrawChunks( VertexBufferObject* VBO )
{
	for ( unsigned short i = 0; i < sizeof( chunks ) / sizeof( chunks[0] ); i++ )					  // Iterate Y
		for ( unsigned short j = 0; j < sizeof( chunks[0] ) / sizeof( chunks[0][0] ); j++ )			  // Iterate Z
			for ( unsigned short k = 0; k < sizeof( chunks[0][0] ) / sizeof( chunks[0][0][0] ); k++ ) // Iterate X
				chunks[i][j][k].DrawMesh( VBO );
}
