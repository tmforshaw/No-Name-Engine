#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

class EntityBufferObject
{
private:
	unsigned int ID;

public:
	EntityBufferObject( GLsizeiptr size, const void* data, GLenum usage );
	~EntityBufferObject();
};