#pragma once
#include "Chunk.hpp"
#include "Cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class World
{
private:
public:
	Chunk chunks[1][1][1];

public:
	World();

	void DrawChunks( VertexBufferObject* VBO );
};