#include "Textures.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <USER/stb_image.h>
#include <glad/glad.h>
#include <iostream>

Texture::Texture( const char* path )
{
	glGenTextures( 1, &ID ); // Generate a GL Texture

	glBindTexture( GL_TEXTURE_2D, ID ); // Bind the texture so it can be modified

	// Set the texture parameteres
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Set stbi to flip the image vertically when it loads
	stbi_set_flip_vertically_on_load( true );

	// Load the image using stb_image.h
	data = stbi_load( path, &width, &height, &channelAmt, 0 );

	if ( data )
	{
		// Generate the texture and mipmap
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );

		std::cout << "Loaded texture of size " << width << "px x " << height << "px" << std::endl;
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	// Free the image from memory
	stbi_image_free( data );
}

void Texture::Bind()
{
	// Activate this texture, then bind it to GL_TEXTURE_2D
	glActiveTexture( GL_TEXTURE0 + ( ID - 1 ) );
	glBindTexture( GL_TEXTURE_2D, ID );
}

// namespace TextureAtlas
// {
// 	void GetTexPos( unsigned short ID, float ( &outArray )[8] )
// 	{
// 		unsigned short i = ID / (float)this->width, j = ID % this->width;

// 		outArray[0] = (float)j * SPRITE_WIDTH / (float)this->width;
// 		outArray[1] = (float)i * SPRITE_HEIGHT / (float)this->height;

// 		outArray[2] = (float)( j + 1 ) * SPRITE_WIDTH / (float)this->width;
// 		outArray[3] = (float)i * SPRITE_HEIGHT / (float)this->height;

// 		outArray[4] = (float)( j + 1 ) * SPRITE_WIDTH / (float)this->width;
// 		outArray[5] = (float)( i + 1 ) * SPRITE_HEIGHT / (float)this->height;

// 		outArray[6] = (float)j * SPRITE_WIDTH / (float)this->width;
// 		outArray[7] = (float)( i + 1 ) * SPRITE_HEIGHT / (float)this->height;
// 	}
// } // namespace TextureAtlas
