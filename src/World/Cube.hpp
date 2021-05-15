#pragma once

#include "../Buffers/Vertex.hpp"

#include <bitset>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum class Face : unsigned short
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

#define FACE_COUNT 6

constexpr std::initializer_list<const Face> faceItr { Face::FRONT, Face::BACK, Face::LEFT, Face::RIGHT, Face::TOP, Face::BOTTOM };

class Cube
{
private:
	unsigned short m_blockID;
	unsigned short m_textureIDs[FACE_COUNT];

public:
	Cube( const unsigned short& p_blockID );

	void GetVertices( std::vector<Vertex>* p_vertices, std::vector<unsigned short>* p_indices );

	static void PushFaceWithMatrix( std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices, const unsigned short& p_blockID, const Face& face, const glm::mat4& matrix );
};