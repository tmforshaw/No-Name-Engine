#pragma once
#include <glad/glad.h>

class EntityBufferObject
{
private:
	unsigned int ID;

public:
	EntityBufferObject();
	EntityBufferObject( GLsizeiptr size, const void* data, GLenum usage );
	~EntityBufferObject();
};