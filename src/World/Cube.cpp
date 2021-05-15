#include "Cube.hpp"

#include "Blocks/Blocks.hpp"

#include <iostream>

// Create an array of the arrays of vertices
const static float cubeVertices[][5 * 4] {

	// Front face
	{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 1.0f, 0.0f },

	// Back face
	{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  -0.5f, 0.5f, 0.5f, 0.0f, 1.0f },

	// Left face
	{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	  -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	  -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f },

	// Right face
	{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	  0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  0.5f, -0.5f, 0.5f, 1.0f, 0.0f },

	// Top face
	{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
	  -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  0.5f, 0.5f, -0.5f, 1.0f, 0.0f },

	// Bottom face
	{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	  0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
	  -0.5f, -0.5f, 0.5f, 0.0f, 1.0f }
};

const static unsigned short faceIndices[]	 = { 0, 1, 2, 2, 3, 0 };
constexpr unsigned short	faceVerticesSize = sizeof( cubeVertices[0] );

Cube::Cube( const unsigned short& p_blockID )
	: m_blockID( p_blockID )
{
	// Initialise the texture IDs
	for ( unsigned short i = 0; i < FACE_COUNT; i++ )
	{
		if ( i % 2 == 0 )
			m_textureIDs[i] = m_blockID;
		else
			m_textureIDs[i] = 2;
	}
}

void Cube::PushFaceWithMatrix( std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices, const unsigned short& p_blockID, const Face& face, const glm::mat4& matrix )
{
	unsigned short finalIndexOfVertices = p_vertices->size(); // Get how many vertices are already in p_vertices

	for ( const auto& index : faceIndices )					  // Iterate through the indices
		p_indices->push_back( index + finalIndexOfVertices ); // Add the offset of finalIndexOfVertices

	// Add each vertex to the vertices vector
	Vertex vert;

	for ( unsigned short i = 0; i < 4; i++ ) // Iterate each vertex of the vertices vector
	{
		vert = {};

		for ( unsigned short j = 0; j < 6; j++ ) // Iterate each element (and one more)
		{
			if ( j < 3 )															// Adding positions
				vert.m_position[j] = cubeVertices[(unsigned short)face][i * 5 + j]; // Add the element from vertices to the vertices vector
			else if ( j < 5 )														// Adding uvCoords
				vert.m_uvCoords[j - 3] = cubeVertices[(unsigned short)face][i * 5 + j];
			else
				vert.m_ID = GetTexture( p_blockID, face ); // Add the correct face texture
		}

		// Calculate the position with the matrix transformation
		glm::vec4 transformedPosition = matrix * glm::vec4( vert.m_position[0], vert.m_position[1], vert.m_position[2], 1.0f );

		// Set the values inside the vertex
		vert.m_position[0] = transformedPosition.x;
		vert.m_position[1] = transformedPosition.y;
		vert.m_position[2] = transformedPosition.z;

		// Add the vertex to the vertices vector
		p_vertices->push_back( vert );
	}
}