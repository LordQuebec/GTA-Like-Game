#include "VBO.h"


VBO::VBO()
	:m_drawMode(GL_TRIANGLES), m_numberOfVertex(0), m_modelMatrix(1)
{}


void VBO::SendData(GLenum p_usage, std::vector<glm::vec3> &p_pos, std::vector<glm::vec4> &p_color)
{
	assert(p_pos.size() == p_color.size());

	m_numberOfVertex = p_pos.size();

	GLsizeiptr vertexCount = sizeof(GLfloat) * m_numberOfVertex;

	glGenBuffers(Array_Size(m_vertexID), &m_vertexID[0]);

	SendBufferData(VBO_POS_ID, vertexCount * 3, &p_pos[0], p_usage);
	SendBufferData(VBO_COLOR_ID, vertexCount * 4, &p_color[0], p_usage);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	m_modelMatrixUniformLocation = OpenGL->GetUniformLocation("ModelMatrix");
}

void VBO::SendBufferData(GLuint p_id, int p_count, const GLvoid* p_data, GLenum p_usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID[p_id]);
	glBufferData(GL_ARRAY_BUFFER, p_count, p_data, p_usage);
}

void VBO::EnableVertexAttrib(GLuint p_id, GLint p_size, GLenum p_type)
{
	glEnableVertexAttribArray(p_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID[p_id]);
	glVertexAttribPointer(p_id, p_size, p_type, GL_FALSE, 0, 0);
}


void VBO::Render()
{
	EnableVertexAttrib(VBO_POS_ID, 3, GL_FLOAT);
	EnableVertexAttrib(VBO_COLOR_ID, 4, GL_FLOAT);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elmArrayBuf);

	//glDrawElements(m_drawMode, m_numberOfVertex, GL_UNSIGNED_SHORT, NULL);
	
	glUniformMatrix4fv(m_modelMatrixUniformLocation, 1, GL_FALSE, &m_modelMatrix[0][0]);
	
	glDrawArrays(m_drawMode, 0, m_numberOfVertex);

	glDisableVertexAttribArray(VBO_COLOR_ID);
	glDisableVertexAttribArray(VBO_POS_ID);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}


void VBO::Translate(const glm::vec3 &p_trans)
{
	m_modelMatrix *= glm::translate(m_modelMatrix, p_trans);
}

void VBO::Rotate(const float p_angle, const glm::vec3 &p_axis)
{
	m_modelMatrix = glm::rotate(m_modelMatrix, p_angle, p_axis);
}

void VBO::Scale(const glm::vec3 &p_scale)
{
	m_modelMatrix = glm::scale(m_modelMatrix, p_scale);
}


VBO::~VBO()
{
	glDeleteBuffers(Array_Size(m_vertexID), &m_vertexID[0]);
}