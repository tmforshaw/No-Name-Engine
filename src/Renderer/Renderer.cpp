#include "Renderer.hpp"

void Renderer::Clear( const float& r, const float& g, const float& b, const float& a )
{
	// Clear the buffers
	glClearColor( r, g, b, a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear the frame buffer
}

void Renderer::Draw( const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader )
{
	// Bind buffers
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements( GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr );
}