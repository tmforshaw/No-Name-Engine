#pragma once

#include "../Buffers/IndexBuffer.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Shader/Shader.hpp"

class Renderer
{
public:
	static void Clear( const float& r = 0.2, const float& g = 0.3, const float& b = 0.3, const float& a = 1.0f );
	static void Draw( const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader );
};