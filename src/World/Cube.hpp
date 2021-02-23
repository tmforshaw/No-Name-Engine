#pragma once
#include "../Textures/TextureAtlas.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define CUBEFACESIZE 6

enum class Face
{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	BOTTOM,
	TOP
};

constexpr std::initializer_list<Face> FaceItr = { Face::FRONT, Face::BACK, Face::RIGHT, Face::LEFT, Face::BOTTOM, Face::TOP };

namespace Cube
{
	// clang-format off
	// The unique vertices of the shape
	static float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0 -0
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1 -1
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2 -2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3 -3
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4 -0
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5 -1
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6 -2
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7 -3
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 13 -0
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8 -1
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 9 -2
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 10 -3
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 15 -0
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 11 -1
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 14 -2
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f  // 12 -3
	};
	// clang-format on

	// Store the indices of which vertex to draw (Each line is a face)
	static unsigned short indices[] = {
		0, 2, 1, 2, 0, 3,	  // Front Face
		4, 5, 6, 6, 7, 4,	  // Back Face
		9, 10, 11, 11, 4, 9,  // Right Face
		13, 15, 2, 15, 13, 8, // Left Face
		11, 14, 5, 5, 4, 11,  // Bottom Face
		3, 13, 2, 13, 3, 12	  // Top Face
	};

	void GetFace( Face face, float ( &array )[5 * 6] );

	void PushFace( std::vector<float> *vector, const Face &face );
	void PushFaceWithMatrix( std::vector<float> *vector, TextureAtlas texSheet, unsigned short type, const Face &face, glm::mat4 model );

} // namespace Cube