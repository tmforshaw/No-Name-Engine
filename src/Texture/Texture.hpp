#pragma once

#define TEX_ATLAS_WIDTH	 8.0f // The width of the texture atlas (in images)
#define TEX_ATLAS_HEIGHT 8.0f // The height of the texture atlas (in images)

class Texture
{
private:
	unsigned int   m_rendererID;
	const char*	   m_filepath;
	unsigned char* m_localBuffer;
	int			   m_width, m_height, m_BPP; // Bits per pixel

public:
	Texture( const char* path );
	~Texture();

	void Bind( const unsigned int& slot = 0 ) const;
	void UnBind() const;

	inline const unsigned int GetWidth() const { return m_width; }
	inline const unsigned int GetHeight() const { return m_height; }
	inline const unsigned int GetBPP() const { return m_BPP; }
};