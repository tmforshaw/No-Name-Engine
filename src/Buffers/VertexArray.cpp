#include "VertexArray.hpp"

// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

VertexArray::VertexArray()
{
	glGenVertexArrays( 1, &m_rendererID );
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays( 1, &m_rendererID );
}

void VertexArray::Bind() const
{
	glBindVertexArray( m_rendererID );
}

void VertexArray::UnBind() const
{
	glBindVertexArray( 0 );
}

void VertexArray::AddBuffer( const VertexBuffer& vb, const BufferLayout& layout ) const
{
	// Bind the buffers
	this->Bind();
	vb.Bind();

	// Get the elements from layout
	const auto&	  elements = layout.GetElements();
	unsigned char offset   = 0;

	for ( unsigned int i = 0; i < elements.size(); i++ ) // Iterate elements
	{
		const auto& element = elements[i];

		// Enable and set the attribute
		glEnableVertexAttribArray( i );

		if ( element.type == GL_FLOAT || element.type == GL_DOUBLE ) // Float or double
			glVertexAttribPointer( i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)offset );
		else // Integer type
			glVertexAttribIPointer( i, element.count, element.type, layout.GetStride(), (const void*)offset );

		// Increment the offset
		offset += BufferElement::GetTypeSize( element.type ) * element.count;
	}
}