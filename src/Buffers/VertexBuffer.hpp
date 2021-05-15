#pragma once

class VertexBuffer
{
private:
	unsigned int m_rendererID;

public:
	VertexBuffer();
	VertexBuffer( const void* data, const unsigned short& size );
	~VertexBuffer();

	void SetData( const void* data, const unsigned short& size ) const;

	void Bind() const;
	void UnBind() const;
};