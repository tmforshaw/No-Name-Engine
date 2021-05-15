#pragma once

class IndexBuffer
{
private:
	unsigned int   m_rendererID;
	unsigned short m_count;

public:
	IndexBuffer();
	IndexBuffer( const unsigned int* data, const unsigned short& count );
	~IndexBuffer();

	void SetData( const unsigned int* data, const unsigned short& count );

	void Bind() const;
	void UnBind() const;

	inline unsigned short GetCount() const { return m_count; }
	inline unsigned int	  ID() const { return m_rendererID; }
};