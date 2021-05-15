#include "IndexBuffer.hpp"
// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

IndexBuffer::IndexBuffer()
	: m_count( 0 )
{
	// Create the buffer
	glGenBuffers( 1, &m_rendererID );
}

IndexBuffer::IndexBuffer( const unsigned int* data, const unsigned short& count )
	: m_count( count )
{
	// Create the buffer
	glGenBuffers( 1, &m_rendererID );

	// Set the data of the buffer
	this->SetData( data, count );
}

IndexBuffer::~IndexBuffer()
{
	// Delete this buffer
	glDeleteBuffers( 1, &m_rendererID );
}

void IndexBuffer::SetData( const unsigned int* data, const unsigned short& count )
{
	// Set m_count
	m_count = count;

	// Bind this buffer
	this->Bind();

	// Set the data of the buffer
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( unsigned int ), data, GL_STATIC_DRAW );
}

void IndexBuffer::Bind() const
{
	// Bind this buffer to GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_rendererID );
}

void IndexBuffer::UnBind() const
{
	// Bind this buffer to NULL
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}