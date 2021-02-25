#include "EntityBufferObject.hpp"

EntityBufferObject::EntityBufferObject()
{
	// Generate and bind the buffer
	glGenBuffers( 1, &ID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ID );
}

EntityBufferObject::EntityBufferObject( GLsizeiptr size, const void* data, GLenum usage )
{
	// Generate and bind the buffer
	glGenBuffers( 1, &ID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ID );

	// Copy the data into the buffer
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
}

EntityBufferObject::~EntityBufferObject()
{
}