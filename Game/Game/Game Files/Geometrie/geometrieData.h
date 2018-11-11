#pragma once

#include <glew.h>

#include "../ThirdParty/glm/vec2.hpp"
#include "../ThirdParty/glm/vec4.hpp"

#include "../Debug/Debug.h"

struct Vertex
{
	glm::vec4 Position;
	glm::vec4 Color;
	glm::vec2 UV;
};


struct ShapeData
{
	ShapeData()
		:vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0) {}
	
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	void CreateVertices(GLuint number)
	{
		numVertices = number;
		vertices = sNew Vertex[number];

		numIndices = number;
		indices = sNew GLushort[number];

		for (int i = 0; i < number; ++i)
		{
			vertices[i] = Vertex();
			indices[i] = i;
		}
	}

	GLsizeiptr VertexBufferSize()const
	{
		return numVertices * sizeof(Vertex);
	}

	GLsizeiptr IndexBufferSize()const
	{
		return numIndices * sizeof(GLushort);
	}

	~ShapeData()
	{
		sDelete(vertices);
		sDelete(indices);
	}
};