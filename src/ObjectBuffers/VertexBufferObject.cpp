#include "VertexBufferObject.hpp"

#include "../Constants.hpp"

VertexBufferObject::VertexBufferObject( GLsizeiptr size, const void* data, GLenum usage )
{
	// Generate the buffer
	glGenBuffers( 1, &ID );

	SetData( size, data, usage );
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers( 1, &ID );
}

unsigned int VertexBufferObject::Get_ID()
{
	return ID;
}

void VertexBufferObject::SetData( GLsizeiptr size, const void* data, GLenum usage )
{
	// Bind the buffer
	glBindBuffer( GL_ARRAY_BUFFER, ID );

	// Copy data into GL_ARRAY_BUFFER
	glBufferData( GL_ARRAY_BUFFER, size, data, usage );

	// Set the structure of the data in the array
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, VERTEXSIZE * sizeof( float ), (void*)0 );						 // Position attribute
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, VERTEXSIZE * sizeof( float ), (void*)( 3 * sizeof( float ) ) ); // Texture map attribute

	// Enable the pointers to that structure
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
}
