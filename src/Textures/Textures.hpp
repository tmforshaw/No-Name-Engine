#pragma once

class Texture
{
public:
	unsigned int   ID;
	int			   width, height, channelAmt;
	unsigned char* data;

	Texture();
	Texture( const char* path );

	void Bind();
};