#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTEXSIZE 5

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
};