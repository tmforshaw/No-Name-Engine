#include "VertexArrayObject.hpp"

#include <glad/glad.h>

VertexArrayObject::VertexArrayObject()
{
	// Generate and bind the buffer
	glGenVertexArrays( 1, &ID );
	glBindVertexArray( ID );
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays( 1, &ID );
}

void VertexArrayObject::Bind()
{
	glBindVertexArray( ID );
}