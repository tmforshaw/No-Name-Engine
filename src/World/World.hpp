#pragma once
#include "../Shader/Shader.hpp"
#include "Chunk.hpp"

#define CHUNKS_X 1
#define CHUNKS_Y 1
#define CHUNKS_Z 1

class World
{
private:
	static Chunk m_chunks[CHUNKS_Y][CHUNKS_Z][CHUNKS_X];

public:
	static void				   Init();
	inline static const Chunk& GetChunk( const unsigned short& x, const unsigned short& y, const unsigned short& z ) { return m_chunks[y][z][x]; }

	static void DrawChunks( const VertexArray& p_VAO, const ShaderProgram& shader );

	static void PushChunkVertices( std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices );
};