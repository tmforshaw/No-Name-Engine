#pragma once
#include "../Cube.hpp"

#define BLOCK_NUM 2

// Face orders: Front, Back, Left, Right, Top, Bottom

const static unsigned short blockArray[BLOCK_NUM][FACE_COUNT] {
	{ 1, 1, 1, 1, 1, 1 }, // Block 1
	{ 2, 2, 2, 2, 2, 2 }  // Block 2
};

unsigned short GetTexture( const unsigned short& p_blockID, const Face& face )
{
	return blockArray[p_blockID][(unsigned short)face];
}