#include "BufferLayout.hpp"

template<>
void BufferLayout::Push<float>( const unsigned int& count )
{
	m_elements.push_back( {
		GL_FLOAT,
		count,
		GL_FALSE // Normalised
	} );

	m_stride += count * BufferElement::GetTypeSize( GL_FLOAT );
}

template<>
void BufferLayout::Push<unsigned int>( const unsigned int& count )
{
	m_elements.push_back( {
		GL_UNSIGNED_INT,
		count,
		GL_FALSE // Normalised
	} );

	m_stride += count * BufferElement::GetTypeSize( GL_UNSIGNED_INT );
}

template<>
void BufferLayout::Push<unsigned short>( const unsigned int& count )
{
	m_elements.push_back( {
		GL_UNSIGNED_SHORT,
		count,
		GL_FALSE // Normalised
	} );

	m_stride += count * BufferElement::GetTypeSize( GL_UNSIGNED_SHORT );
}

template<>
void BufferLayout::Push<unsigned char>( const unsigned int& count )
{
	m_elements.push_back( {
		GL_UNSIGNED_BYTE,
		count,
		GL_TRUE // Normalised
	} );

	m_stride += count * BufferElement::GetTypeSize( GL_UNSIGNED_BYTE );
}