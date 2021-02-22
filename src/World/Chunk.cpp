#include "Chunk.hpp"

#include "../Camera/Projections.hpp"
#include "../Noise/PerlinNoise.hpp"
#include "../Textures/Textures.hpp"
#include "World.hpp"

#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk()
{
	// Set its ID values
	pos_i = 0, pos_j = 0, pos_k = 0;

	// Initialise chunks
	unsigned short cubes[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE] = {};
}

Chunk::Chunk( unsigned short p_i, unsigned short p_j, unsigned short p_k )
{
	// Set its ID values
	pos_i = p_i, pos_j = p_j, pos_k = p_k;

	// Initialise chunks
	unsigned short cubes[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE] = {};

	// Set all values to 1
	Fill( 1 );
}

glm::vec3 Chunk::GetPosition( unsigned short i, unsigned short j, unsigned short k ) const
{
	return glm::vec3( k + pos_k * CHUNKSIZE, i + pos_i * CHUNKSIZE, j + pos_j * CHUNKSIZE );
}

void Chunk::GenerateMesh()
{
	// Reset the mesh and texture
	mesh = {};

	for ( unsigned short i = 0; i < CHUNKSIZE; i++ )		 // Iterate Y
		for ( unsigned short j = 0; j < CHUNKSIZE; j++ )	 // Iterate Z
			for ( unsigned short k = 0; k < CHUNKSIZE; k++ ) // Iterate X
			{
				if ( cubes[i][j][k] != 0 )						  // Is a block
					for ( auto& face : FaceItr )				  // Iterate through Face enum
						if ( GetNeighbour( i, j, k, face ) == 0 ) // Neighbour isn't a block
							Cube::PushFaceWithMatrix( &mesh, face, glm::translate( glm::mat4( 1.0f ), GetPosition( i, j, k ) ) );
			}
}

void Chunk::DrawMesh( VertexBufferObject* VBO ) const
{
	VBO->SetData( mesh.size() * sizeof( float ), mesh.data(), GL_STATIC_DRAW );

	glDrawArrays( GL_TRIANGLES, 0, mesh.size() );
}

unsigned short Chunk::GetCube( unsigned short i, unsigned short j, unsigned short k ) const
{
	return cubes[i][j][k];
}

unsigned short Chunk::GetNeighbourChunkBlock( unsigned short i, unsigned short j, unsigned short k, Face face ) const
{
	unsigned short new_i = i, new_j = j, new_k = k;
	unsigned short chunk_i = pos_i, chunk_j = pos_j, chunk_k = pos_k;

	switch ( face )
	{
	case Face::FRONT:
		new_j = CHUNKSIZE - 1;

		if ( pos_j > 0 )
			chunk_j--;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::BACK:
		new_j = 0;

		if ( pos_j < CHUNKS_Z - 1 )
			chunk_j++;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::RIGHT:
		new_k = CHUNKSIZE - 1;

		if ( pos_k > 0 )
			chunk_k--;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::LEFT:
		new_k = 0;

		if ( pos_k < CHUNKS_X - 1 )
			chunk_k++;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::BOTTOM:
		new_i = CHUNKSIZE - 1;

		if ( pos_i > 0 )
			chunk_i--;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::TOP:
		new_i = 0;

		if ( pos_i < CHUNKS_Y - 1 )
			chunk_i++;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	default:
		// You should never reach here
		break;
	}

	unsigned short test = world.GetChunk( chunk_i, chunk_j, chunk_k ).GetCube( new_i, new_j, new_k );

	return test;
}

unsigned short Chunk::GetNeighbour( unsigned short i, unsigned short j, unsigned short k, Face face ) const
{
	unsigned short new_i = i, new_j = j, new_k = k;

	switch ( face )
	{
	case Face::FRONT:
		if ( j > 0 ) new_j--;
		else
			goto outsideChunk;
		break;

	case Face::BACK:
		if ( j < CHUNKSIZE - 1 ) new_j++;
		else
			goto outsideChunk;
		break;

	case Face::RIGHT:
		if ( k > 0 ) new_k--;
		else
			goto outsideChunk;
		break;

	case Face::LEFT:
		if ( k < CHUNKSIZE - 1 ) new_k++;
		else
			goto outsideChunk;
		break;

	case Face::BOTTOM:
		if ( i > 0 ) new_i--;
		else
			goto outsideChunk;
		break;

	case Face::TOP:
		if ( i < CHUNKSIZE - 1 ) new_i++;
		else
			goto outsideChunk;
		break;

	default:
		// You should never reach here
		break;
	}

	return cubes[new_i][new_j][new_k];

outsideChunk:

	return GetNeighbourChunkBlock( i, j, k, face ); // Index is outside of chunk, check the neighbouring chunk
}

void Chunk::Fill( unsigned short value )
{
	// Seed the random function
	srand( glfwGetTime() );

	// Generate perlin noise
	float noise[NOISE_SIZE_Y][NOISE_SIZE_X];
	PerlinNoise2D( rand(), 6, noise, 0.2f );

	// Reset chunk
	for ( unsigned short j = 0; j < CHUNKSIZE; j++ )		 // Iterate Z
		for ( unsigned short k = 0; k < CHUNKSIZE; k++ )	 // Iterate X
			for ( unsigned short i = 0; i < CHUNKSIZE; i++ ) // Iterate Y
				cubes[i][j][k] = 0;

	for ( unsigned short j = 0; j < CHUNKSIZE; j++ )																						  // Iterate Z
		for ( unsigned short k = 0; k < CHUNKSIZE; k++ )																					  // Iterate X
			for ( unsigned short i = 0; i < (unsigned short)( (float)CHUNKSIZE * noise[pos_j * CHUNKSIZE + j][pos_k * CHUNKSIZE + k] ); i++ ) // Iterate Y
				cubes[i][j][k] = value;
}