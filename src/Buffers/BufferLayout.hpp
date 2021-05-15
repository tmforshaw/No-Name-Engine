#pragma once

// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

#include <iostream>
#include <vector>

struct BufferElement
{
	unsigned int  type;
	unsigned int  count;
	unsigned char normalised;

	static unsigned int GetTypeSize( const unsigned int& type )
	{
		switch ( type )
		{
		case GL_FLOAT: return sizeof( GLfloat );
		case GL_UNSIGNED_INT: return sizeof( GLuint );
		case GL_UNSIGNED_SHORT: return sizeof( GLushort );
		case GL_UNSIGNED_BYTE: return sizeof( GLubyte );

		default:
			std::cout << "ERROR::TYPE::GET_SIZE::UNDEFINED" << std::endl;
			return 0;
		}
	}
};

class BufferLayout
{
private:
	std::vector<BufferElement> m_elements;
	unsigned int			   m_stride;

public:
	BufferLayout()
		: m_stride( 0 ) {}

	template<typename T>
	void Push( const unsigned int& count )
	{
		std::cout << "ERROR::LAYOUT::UNDEFINED_TYPE" << std::endl;
	}

	inline const std::vector<BufferElement> GetElements() const { return m_elements; }
	inline const unsigned int				GetStride() const { return m_stride; }
};
