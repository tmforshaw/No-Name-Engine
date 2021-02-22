#pragma once
#include <glad/glad.h>

class VertexBufferObject
{
private:
	unsigned int ID;

public:
	VertexBufferObject( GLsizeiptr size, const void* data, GLenum usage );
	~VertexBufferObject();

	unsigned int Get_ID();

	void SetData( GLsizeiptr size, const void* data, GLenum usage );
};