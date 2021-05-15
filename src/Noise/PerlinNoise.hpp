#pragma once

#define NOISE_SIZE_X 1024
#define NOISE_SIZE_Y 1024

void SeedNoise( const unsigned short& seed );
void PerlinNoise2D( const unsigned short& seed, const unsigned short& octaveNum, float ( &outArray )[NOISE_SIZE_Y][NOISE_SIZE_Y], const float& fBias = 2.0f );