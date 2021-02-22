#pragma once

class VertexArrayObject
{
private:
	unsigned int ID;

public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind();
};