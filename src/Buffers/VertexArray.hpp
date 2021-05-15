#pragma once
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"

class VertexArray
{
private:
	unsigned int m_rendererID;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer( const VertexBuffer& vb, const BufferLayout& layout ) const;
};