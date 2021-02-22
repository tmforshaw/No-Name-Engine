#pragma once

#define NOISE_SIZE_X 1024
#define NOISE_SIZE_Y 1024

void SeedNoise( unsigned int seed );
void PerlinNoise2D( unsigned int seed, unsigned short octaveNum, float ( &outArray )[NOISE_SIZE_Y][NOISE_SIZE_Y], float fBias = 2.0f );