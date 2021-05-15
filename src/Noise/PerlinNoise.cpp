#include "PerlinNoise.hpp"

// #include <glad/glad.h>
#include <random>

static float noiseSeed[NOISE_SIZE_Y][NOISE_SIZE_X];

void SeedNoise( const unsigned short& seed )
{
	// Seed the random numbers
	srand( seed );

	for ( unsigned short i = 0; i < NOISE_SIZE_Y; i++ )
		for ( unsigned short j = 0; j < NOISE_SIZE_X; j++ )
			noiseSeed[i][j] = (float)rand() / (float)RAND_MAX; // Normalise it
}

void PerlinNoise2D( const unsigned short& seed, const unsigned short& octaveNum, float ( &outArray )[NOISE_SIZE_Y][NOISE_SIZE_Y], const float& fBias )
{
	SeedNoise( seed );

	float		   fNoise, fScale, fScaleAcc, fBlendX, fBlendY, fSample1, fSample2;
	unsigned short stride, sampleX1, sampleX2, sampleY1, sampleY2;

	for ( unsigned short i = 0; i < NOISE_SIZE_Y; i++ )
		for ( unsigned short j = 0; j < NOISE_SIZE_X; j++ )
		{
			fNoise	  = 0.0f;
			fScale	  = 1.0f;
			fScaleAcc = 0.0f;

			for ( unsigned short octave = 0; octave < octaveNum; octave++ )
			{
				stride	 = NOISE_SIZE_X >> octave;
				sampleX1 = ( j / stride ) * stride; // j - ( j % stride );
				sampleY1 = ( i / stride ) * stride; // i - ( i % stride );

				sampleX2 = ( sampleX1 + stride ) % NOISE_SIZE_X;
				sampleY2 = ( sampleY1 + stride ) % NOISE_SIZE_X;

				fBlendX = (float)( j - sampleX1 ) / (float)stride;
				fBlendY = (float)( i - sampleY1 ) / (float)stride;

				// Linear interpolation
				fSample1 = ( 1.0f - fBlendX ) * noiseSeed[sampleY1][sampleX1] + fBlendX * noiseSeed[sampleY1][sampleX2];
				fSample2 = ( 1.0f - fBlendX ) * noiseSeed[sampleY2][sampleX1] + fBlendX * noiseSeed[sampleY2][sampleX2];

				fNoise += ( fBlendY * ( fSample2 - fSample1 ) + ( fSample1 ) ) * fScale; // Combine the samples using linear interpretation

				fScaleAcc += fScale;
				fScale = fScale / fBias;
			}

			outArray[i][j] = fNoise / fScaleAcc;
		}
}