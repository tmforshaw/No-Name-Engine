#pragma once
#include "Textures.hpp"

class TextureAtlas
{
private:
	Texture		   texture;
	unsigned short tileW, tileH;

public:
	TextureAtlas( const char* textureSheetPath );

	void GetTexturePos( unsigned short ID, float ( &outArray )[8] ) const;
};