#pragma once
#include <vector>

class Texture
{
public:
	unsigned int   ID;
	int			   width, height, channelAmt;
	unsigned char* data;

	Texture( const char* path );

	void Bind();
};
