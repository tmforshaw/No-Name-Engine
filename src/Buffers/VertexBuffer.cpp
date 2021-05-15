#include "VertexBuffer.hpp"
// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

VertexBuffer::VertexBuffer()
{
	// Create the buffer
	glGenBuffers( 1, &m_rendererID );
}

VertexBuffer::VertexBuffer( const void* data, const unsigned short& size )
{
	// Create the buffer
	glGenBuffers( 1, &m_rendererID );

	// Set the data of the buffer
	this->SetData( data, size );
}

VertexBuffer::~VertexBuffer()
{
	// Delete this buffer
	glDeleteBuffers( 1, &m_rendererID );
}

void VertexBuffer::SetData( const void* data, const unsigned short& size ) const
{
	// Bind this buffer
	this->Bind();

	// Set the data of the buffer
	glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
}

void VertexBuffer::Bind() const
{
	// Bind this buffer to GL_ARRAY_BUFFER
	glBindBuffer( GL_ARRAY_BUFFER, m_rendererID );
}

void VertexBuffer::UnBind() const
{
	// Bind this buffer to NULL
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}