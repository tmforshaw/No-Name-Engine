#include "VertexArrayObject.hpp"
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

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