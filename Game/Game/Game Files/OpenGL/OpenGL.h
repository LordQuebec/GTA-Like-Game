#pragma once

#include <Windows.h>
#include <glew.h>
#include <gl\GLU.h>

#include <fstream>
#include <vector>

#include "../Debug/Debug.h"
#include "../Struct/Color/Color.h"
#include "../ThirdParty/glm/vec2.hpp"
#include "../ThirdParty/glm/matrix.hpp"
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"

class OGL
{
private:
	OGL();
	static OGL* m_instance;

	Color m_clearColor;
	GLbitfield m_clearFlag;

	HDC m_hdc;
	HGLRC m_hglrc;

	GLuint m_shaderProgramID;
	glm::mat4 m_projectionMatrix;

	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	bool ReadShader(const char* path, std::string &shaderCode)const;
	bool CompileShader(const GLuint ShaderID, const std::string &ShaderCode, std::vector<char>ErrorMsg)const;

public:
	static OGL* CreateInstance();
	static OGL* GetInstance() { return m_instance; }

	void Enable(HWND handle, const Color &clearColor, const float fov, const float nearPlane, const float farPlane, const glm::vec2 &viewPortSize);
	void Disable(HWND handle);

	void ClearScreen();
	void SwapBuffer() { SwapBuffers(m_hdc); }

	void ResizeViewPort(GLint X, GLint Y, GLsizei Width, GLsizei height) { glViewport(X, Y, Width, height);}
	void ResizeViewPort(GLsizei width, GLsizei height) { glViewport(0, 0, width, height); }
	void ResizeViewPort(glm::vec2 size) {
		glViewport(0, 0, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y));

		m_projectionMatrix = glm::perspective(m_fov, size.x / size.y, m_nearPlane, m_farPlane);
	}

	GLuint LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath);

	GLint GetUniformLocation(const std::string &Name)const;
	glm::mat4 GetProjection() { return m_projectionMatrix; }

	void SetClearColor(const Color &color) { m_clearColor = color; }
	void SetClearFlag(const GLbitfield flag) { m_clearFlag = flag; }

	~OGL() { m_instance = nullptr; }
};

extern OGL* OpenGL;