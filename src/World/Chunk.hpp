#pragma once
#include "../ObjectBuffers/VertexBufferObject.hpp"
#include "Cube.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define CHUNKSIZE 16

class Chunk
{
private:
	unsigned short	   pos_i, pos_j, pos_k;
	unsigned short	   cubes[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
	std::vector<float> mesh;

public:
	Chunk();
	Chunk( unsigned short p_i, unsigned short p_j, unsigned short p_k );

	glm::vec3 GetPosition( unsigned short i, unsigned short j, unsigned short k ) const;

	void GenerateMesh();
	void DrawMesh( VertexBufferObject* VBO ) const;

	unsigned short GetCube( unsigned short i, unsigned short j, unsigned short k ) const;
	unsigned short GetNeighbourChunkBlock( unsigned short i, unsigned short j, unsigned short k, Face face ) const;
	unsigned short GetNeighbour( unsigned short i, unsigned short j, unsigned short k, Face face ) const;

	void Fill( unsigned short value );
};