#pragma once


#include <glew.h>

#include <vector>

#include "../ThirdParty/glm/vec3.hpp"
#include "../ThirdParty/glm/vec4.hpp"

#include "../Math/Math.h"


#define VBO_POS_ID 0
#define VBO_COLOR_ID 1
#define VBO_TEXTURE_COORD_ID 2
#define VBO_NORMAL_ID 3


class VBO
{
private:
	GLuint m_vertexID[4] = { 0, 0, 0, 0 };
	GLenum m_drawMode;

	GLuint m_elmArrayBuf;

	size_t  m_numberOfVertex;

	void SendBufferData(GLuint ID, int vertexCount, const GLvoid* data, GLenum usage);
	void EnableVertexAttrib(GLuint ID, GLint size, GLenum type);

public:
	VBO();

	void SendData(GLenum usage, std::vector<glm::vec3> &pos, std::vector<glm::vec4> &colors);

	void Render();
	//void Render(const GLenum mode)const;

	size_t GetNumberOfVertex()const { return m_numberOfVertex; }
	void SetDrawMode(GLenum mode) { m_drawMode = mode; }

	~VBO();
};