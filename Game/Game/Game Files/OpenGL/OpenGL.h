#pragma once

#include <Windows.h>
#include <glew.h>
#include <gl\GLU.h>

#include <fstream>
#include <vector>

#include "../Debug/Debug.h"
#include "../Struct/Color/Color.h"
#include "../ThirdParty/glm/vec2.hpp"

class OGL
{
private:
	OGL();
	static OGL* m_instance;

	Color m_clearColor;
	GLbitfield m_clearFlag;

	HDC m_hdc;
	HGLRC m_hglrc;

	bool ReadShader(const char* path, std::string &shaderCode)const;
	bool CompileShader(const GLuint ShaderID, const std::string &ShaderCode, std::vector<char>ErrorMsg)const;

public:
	static OGL* CreateInstance();
	static OGL* GetInstance() { return m_instance; }

	void Enable(HWND handle, const Color &clearColor, const glm::vec2 &viewPortSize);
	void Disable(HWND handle);

	void ClearScreen();
	void SwapBuffer() { SwapBuffers(m_hdc); }

	void ResizeViewPort(GLint X, GLint Y, GLsizei Width, GLsizei height) { glViewport(X, Y, Width, height); }
	void ResizeViewPort(GLsizei width, GLsizei height) { glViewport(0, 0, width, height); }
	void ResizeViewPort(glm::vec2 size) { glViewport(0, 0, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y)); }

	GLuint LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath)const;

	void SetClearColor(const Color &color) { m_clearColor = color; }
	void SetClearFlag(const GLbitfield flag) { m_clearFlag = flag; }

	~OGL() { m_instance = nullptr; }
};

extern OGL* OpenGL;