#include "Chunk.hpp"

#include "../Camera/Projections.hpp"

#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk()
{
	// Set its ID values
	i = 0, j = 0, k = 0;

	// Initialise chunks
	unsigned short cubes[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE] = {};
}

Chunk::Chunk( unsigned short p_i, unsigned short p_j, unsigned short p_k )
{
	// Set its ID values
	i = p_i, j = p_j, k = p_k;

	// Initialise chunks
	unsigned short cubes[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE] = {};

	// Set all values to 1
	Fill( 1 );
}

glm::vec3 Chunk::GetPosition( unsigned short i, unsigned short j, unsigned short k )
{
	return glm::vec3( j, i, k );
}

void Chunk::GenerateMesh()
{
	for ( unsigned short i = 0; i < sizeof( cubes ) / sizeof( cubes[0] ); i++ )						// Iterate Y
		for ( unsigned short j = 0; j < sizeof( cubes[0] ) / sizeof( cubes[0][0] ); j++ )			// Iterate Z
			for ( unsigned short k = 0; k < sizeof( cubes[0][0] ) / sizeof( cubes[0][0][0] ); k++ ) // Iterate X
			{
				if ( cubes[i][j][k] != 0 ) // Is a block
				{
					// Cube::PushCubeWithMatrix( mesh, glm::translate( glm::mat4( 1.0f ), GetPosition( i, j, k ) ) );

					for ( auto& face : FaceItr ) // Iterate through Face enum
					{
						if ( GetNeighbour( i, j, k, face ) == 0 ) // Neighbour isn't a block
						{
							Cube::PushFaceWithMatrix( &mesh, face, glm::translate( glm::mat4( 1.0f ), GetPosition( i, j, k ) ) );
						}
					}
				}
			}
}

void Chunk::DrawMesh( VertexBufferObject* VBO )
{
	VBO->SetData( mesh.size() * sizeof( float ), mesh.data(), GL_STATIC_DRAW );

	glDrawArrays( GL_TRIANGLES, 0, mesh.size() );
}

unsigned short Chunk::GetNeighbour( unsigned short i, unsigned short j, unsigned short k, Face face )
{
	unsigned short new_i = i, new_j = j, new_k = k;

	switch ( face )
	{
	case Face::FRONT:
		if ( j > 0 ) new_j--;
		else
			return 0; // Return that it is an air block because it is outside of the chunk
		break;

	case Face::BACK:
		if ( j < CHUNKSIZE - 1 ) new_j++;
		else
			return 0; // Return that it is an air block because it is outside of the chunk
		break;

	case Face::RIGHT:
		if ( k > 0 ) new_k--;
		else
			return 0; // Return that it is an air block because it is outside of the chunk
		break;

	case Face::LEFT:
		if ( k < CHUNKSIZE - 1 ) new_k++;
		else
			return 0; // Return that it is an air block because it is outside of the chunk
		break;

	case Face::BOTTOM:
		if ( i > 0 ) new_i--;
		else
			return 0; // Return that it is an air block because it is outside of the chunk
		break;

	case Face::TOP:
		if ( i < CHUNKSIZE - 1 ) new_i++;
		else
			return 0; // Return that it is an air block because it is outside of the chunk
		break;

	default:
		// You should never reach here
		break;
	}

	return cubes[new_i][new_j][new_k];
}

void Chunk::Fill( unsigned short value )
{
	for ( unsigned short i = 0; i < sizeof( cubes ) / sizeof( cubes[0] ); i++ )						// Iterate Y
		for ( unsigned short j = 0; j < sizeof( cubes[0] ) / sizeof( cubes[0][0] ); j++ )			// Iterate Z
			for ( unsigned short k = 0; k < sizeof( cubes[0][0] ) / sizeof( cubes[0][0][0] ); k++ ) // Iterate X
				cubes[i][j][k] = value;
}