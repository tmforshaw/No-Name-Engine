#pragma once
#include "../Buffers/IndexBuffer.hpp"
#include "../Buffers/Vertex.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Shader/Shader.hpp"
#include "../Types/SmartPtr.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CHUNK_SIZE 16

class Chunk
{
private:
	unsigned short			  m_posX, m_posY, m_posZ;
	unsigned short			  m_cubes[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	std::vector<Vertex>		  m_mesh;
	std::vector<unsigned int> m_indices;
	// VertexBuffer				m_vertexBuffer;
	// IndexBuffer					m_indexBuffer;

	// SmartPtr<VertexBuffer>		m_vertexBuffer;
	// VertexBuffer				 m_vertexBuffer1;
	// std::unique_ptr<IndexBuffer> m_indexBuffer1;

public:
	Chunk();
	Chunk( const unsigned short& p_posX, const unsigned short& p_posY, const unsigned short& p_posZ );

	inline const unsigned short GetCube( const unsigned short& x, const unsigned short& y, const unsigned short& z ) const { return m_cubes[y][z][x]; }
	inline const glm::vec3		GetPosition( const unsigned short& x, const unsigned short& y, const unsigned short& z ) const { return glm::vec3( x + m_posX * CHUNK_SIZE, y + m_posY * CHUNK_SIZE, z + m_posZ * CHUNK_SIZE ); }

	unsigned short GetNeighbourChunkBlock( const unsigned short& x, const unsigned short& y, const unsigned short& z, const Face& face ) const;
	unsigned short GetNeighbour( const unsigned short& x, const unsigned short& y, const unsigned short& z, const Face& face ) const;

	void GenerateMesh();
	void DrawMesh( const VertexArray& p_VAO, const ShaderProgram& shader ) const;

	void PushVertices( std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices );
};