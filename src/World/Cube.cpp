#include "Cube.hpp"

#include "../Constants.hpp"

namespace Cube
{
	void GetFace( Face face, float ( &array )[VERTEXSIZE * CUBEFACESIZE] )
	{
		// Add all the vertices of the face to the array
		for ( unsigned short i = 0; i < CUBEFACESIZE; i++ )	  // Iterate indices
			for ( unsigned short j = 0; j < VERTEXSIZE; j++ ) // Iterate through all the vertex floats
				array[i * VERTEXSIZE + j] = vertices[indices[(short)face * CUBEFACESIZE + i] * 5 + j];
	}

	void PushFace( std::vector<float> *vector, const Face &face )
	{
		// Add all the vertices of the face to the vector
		for ( unsigned short i = 0; i < CUBEFACESIZE; i++ )	  // Iterate indices
			for ( unsigned short j = 0; j < VERTEXSIZE; j++ ) // Iterate through all the vertex floats
				vector->push_back( vertices[indices[(short)face * CUBEFACESIZE + i] * VERTEXSIZE + j] );
	}

	void PushFaceWithMatrix( std::vector<float> *vector, TextureAtlas texSheet, unsigned short type, const Face &face, glm::mat4 model )
	{
		for ( unsigned short i = 0; i < CUBEFACESIZE; i++ ) // Iterate indices
		{
			std::vector<float> position = {}, texCoords = {};

			for ( unsigned short j = 0; j < VERTEXSIZE; j++ ) // Iterate through all the vertex floats
				if ( j < 3 )								  // Add to position or texCoords depending on index
					position.push_back( vertices[indices[(short)face * CUBEFACESIZE + i] * VERTEXSIZE + j] );
				else
					texCoords.push_back( vertices[indices[(short)face * CUBEFACESIZE + i] * VERTEXSIZE + j] );

			glm::vec4 projectedPosition = model * glm::vec4( position[0], position[1], position[2], 1.0f );

			// Add the point to the vector
			vector->push_back( projectedPosition.x );
			vector->push_back( projectedPosition.y );
			vector->push_back( projectedPosition.z );

			float texCoordArray[8];
			texSheet.GetTexturePos( type - 1, texCoordArray );

			unsigned short texCoordType = indices[(short)face * CUBEFACESIZE + i] % 4;

			// Push the coordinates
			vector->push_back( texCoordArray[texCoordType * 2] );
			vector->push_back( texCoordArray[texCoordType * 2 + 1] );
		}
	}

} // namespace Cube