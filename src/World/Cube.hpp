#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define CUBEFACESIZE 6

enum class Face
{
	RIGHT,
	LEFT,
	FRONT,
	BACK,
	BOTTOM,
	TOP
};

constexpr std::initializer_list<Face> FaceItr = { Face::RIGHT, Face::LEFT, Face::FRONT, Face::BACK, Face::BOTTOM, Face::TOP };

namespace Cube
{
	// clang-format off
	// The unique vertices of the shape
	static float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 9
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 10
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 11
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 12
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 13
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 14
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 15
	};
	// clang-format on

	// Store the indices of which vertex to draw (Each line is a face)
	static unsigned int indices[] = {
		0, 2, 1, 2, 0, 3,	   // Front Face
		4, 5, 6, 6, 7, 4,	   // Back Face
		8, 9, 10, 10, 4, 8,	   // Right Face
		11, 12, 2, 12, 11, 13, // Left Face
		10, 14, 5, 5, 4, 10,   // Bottom Face
		3, 11, 2, 11, 3, 15	   // Top Face
	};

	void GetFace( Face face, float ( &array )[5 * 6] );

	void PushFace( std::vector<float> *vector, const Face &face );
	void PushFaceWithMatrix( std::vector<float> *vector, const Face &face, glm::mat4 model );

	void PushCube( std::vector<float> *vector );
	void PushCubeWithMatrix( std::vector<float> *vector, glm::mat4 model );

} // namespace Cube