#include "Cube.hpp"

#include "../Constants.hpp"

namespace Cube
{
	void GetFace( Face face, float ( &array )[VERTEX_POSITION_SIZE * CUBEFACESIZE] )
	{
		// Add all the vertices of the face to the array
		for ( unsigned short i = 0; i < CUBEFACESIZE; i++ )				// Iterate indices
			for ( unsigned short j = 0; j < VERTEX_POSITION_SIZE; j++ ) // Iterate through all the vertex floats
				array[i * VERTEX_POSITION_SIZE + j] = vertexPositions[indices[(short)face * CUBEFACESIZE + i] * 5 + j];
	}

	void PushFace( std::vector<float> *vector, TextureAtlas texSheet, unsigned short blockID, const Face &face )
	{
		// Add all the vertices of the face to the vector
		for ( unsigned short i = 0; i < CUBEFACESIZE; i++ ) // Iterate indices
		{
			for ( unsigned short j = 0; j < VERTEX_POSITION_SIZE; j++ ) // Iterate through all the vertex floats
				vector->push_back( vertexPositions[indices[(short)face * CUBEFACESIZE + i] * VERTEX_POSITION_SIZE + j] );

			float texCoordArray[8];
			texSheet.GetTexturePos( blockID - 1, texCoordArray );

			unsigned short texCoordType = indices[(short)face * CUBEFACESIZE + i] % 4;

			// Push the coordinates
			vector->push_back( texCoordArray[texCoordType * 2] );
			vector->push_back( texCoordArray[texCoordType * 2 + 1] );
		}
	}

	void PushFaceWithMatrix( std::vector<float> *vector, TextureAtlas texSheet, unsigned short blockID, const Face &face, glm::mat4 model )
	{
		for ( unsigned short i = 0; i < CUBEFACESIZE; i++ ) // Iterate indices
		{
			std::vector<float> position = {}, texCoords = {};

			for ( unsigned short j = 0; j < VERTEX_POSITION_SIZE; j++ ) // Iterate through all the vertex floats
				position.push_back( vertexPositions[indices[(short)face * CUBEFACESIZE + i] * VERTEX_POSITION_SIZE + j] );

			glm::vec4 projectedPosition = model * glm::vec4( position[0], position[1], position[2], 1.0f );

			// Add the point to the vector
			vector->push_back( projectedPosition.x );
			vector->push_back( projectedPosition.y );
			vector->push_back( projectedPosition.z );

			float texCoordArray[8];
			texSheet.GetTexturePos( blockID - 1, texCoordArray );

			unsigned short texCoordType = indices[(short)face * CUBEFACESIZE + i] % 4;

			// Push the coordinates
			vector->push_back( texCoordArray[texCoordType * 2] );
			vector->push_back( texCoordArray[texCoordType * 2 + 1] );
		}
	}

} // namespace Cube