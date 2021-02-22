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
	unsigned short	   i, j, k;
	unsigned short	   cubes[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
	std::vector<float> mesh;

public:
	Chunk();
	Chunk( unsigned short p_i, unsigned short p_j, unsigned short p_k );

	glm::vec3 GetPosition( unsigned short i, unsigned short j, unsigned short k );

	void GenerateMesh();
	void DrawMesh( VertexBufferObject* VBO );

	unsigned short GetNeighbour( unsigned short i, unsigned short j, unsigned short k, Face face );

	void Fill( unsigned short value );
};