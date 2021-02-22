#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

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