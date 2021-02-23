#include "TextureAtlas.hpp"

#define TILE_W 128
#define TILE_H 128

TextureAtlas::TextureAtlas( const char* textureSheetPath )
	: texture( Texture( textureSheetPath ) )
{
	this->tileW = TILE_W;
	this->tileH = TILE_H;
}

void TextureAtlas::GetTexturePos( unsigned short ID, float ( &outArray )[8] ) const
{
	unsigned short i = ID / this->texture.width, j = ID % this->texture.width;

	outArray[0] = (float)j * this->tileW / (float)this->texture.width;
	outArray[1] = (float)i * this->tileH / (float)this->texture.height;

	outArray[2] = (float)( j + 1 ) * this->tileW / (float)this->texture.width;
	outArray[3] = (float)i * this->tileH / (float)this->texture.height;

	outArray[4] = (float)( j + 1 ) * this->tileW / (float)this->texture.width;
	outArray[5] = (float)( i + 1 ) * this->tileH / (float)this->texture.height;

	outArray[6] = (float)j * this->tileW / (float)this->texture.width;
	outArray[7] = (float)( i + 1 ) * this->tileH / (float)this->texture.height;
}