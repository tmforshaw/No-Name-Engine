#include "Texture.hpp"

#include <USER/stb_image.h>
#include <glad/glad.h>

Texture::Texture( const char* path )
	: m_rendererID( 0 ), m_filepath( path ), m_localBuffer( nullptr ), m_width( 0 ), m_height( 0 ), m_BPP( 0 )
{
	// Load the image from a file
	stbi_set_flip_vertically_on_load( true );
	m_localBuffer = stbi_load( path, &m_width, &m_height, &m_BPP, 4 ); // 4 Channels (RGBA)

	// Generate the texture buffer
	glGenTextures( 1, &m_rendererID );
	glBindTexture( GL_TEXTURE_2D, m_rendererID );

	// Specify the texture parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	// Pass the data to OpenGL
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer );

	if ( m_localBuffer )				  // If it contains data
		stbi_image_free( m_localBuffer ); // Free memory
}

Texture::~Texture()
{
	glDeleteTextures( 1, &m_rendererID );
}

void Texture::Bind( const unsigned int& slot ) const
{
	glActiveTexture( GL_TEXTURE0 + slot );
	glBindTexture( GL_TEXTURE_2D, m_rendererID );
}

void Texture::UnBind() const
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}