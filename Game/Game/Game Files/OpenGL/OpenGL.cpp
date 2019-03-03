#include "OpenGL.h"

#include "../ThirdParty/glm/gtc/matrix_transform.hpp"

OGL* OGL::m_instance = nullptr;

OGL::OGL()
	:m_clearColor(Color()), m_clearFlag(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), m_projectionMatrix(glm::mat4(1.0f))
{}


OGL* OGL::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew OGL();
	return m_instance;
}


void OGL::Enable(HWND p_handle, const Color &p_clearColor, const float p_fov, const float p_nearPlane, const float p_farPlane, const glm::vec2 &p_viewSize)
{
	m_clearColor = p_clearColor;
	m_fov = p_fov;

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	m_hdc = GetDC(p_handle);

	SetPixelFormat(m_hdc, ChoosePixelFormat(m_hdc, &pfd), &pfd);

	m_hglrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hglrc);

	if (glewInit() != GLEW_OK)
		ERR_MSG("Glew init failure");

	glViewport(0, 0, static_cast<GLsizei>(p_viewSize.x), static_cast<GLsizei>(p_viewSize.y));

	m_projectionMatrix = glm::perspective(m_fov = p_fov, p_viewSize.x / p_viewSize.y, m_nearPlane = p_nearPlane, m_farPlane = p_farPlane);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void OGL::Disable(HWND p_handle)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hglrc);
	ReleaseDC(p_handle, m_hdc);
}

void OGL::ClearScreen()
{
	glClearColor(m_clearColor.R, m_clearColor.G, m_clearColor.B, m_clearColor.A);
	glClear(m_clearFlag);
}

GLuint OGL::LoadShader(const char* p_vPath, const char* p_fPath)
{
	//Create IDs
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	if (!ReadShader(p_vPath, vertexShaderCode))
	{
		ERR_MSG("Can't read vertex Shader");
		return 0;
	}
	if (!ReadShader(p_fPath, fragmentShaderCode))
	{
		ERR_MSG("Can't read fragmentShader");
		return 0;
	}

	std::vector<char>ErrorMsg;

	//Log Compiling Vertex Shader
	if (!CompileShader(vertexShaderID, vertexShaderCode, ErrorMsg))//Compile error
	{
		ERR_MSG("Error Compiling Vertex shader");
		//Log ErrorMsg
		return 0;
	}
	//Log Compiling Fragment Shader
	if (!CompileShader(fragmentShaderID, fragmentShaderCode, ErrorMsg))//Compile error
	{
		ERR_MSG("Error Compiling Fragment shader");
		//Log ErrorMsg
		return 0;
	}

	m_shaderProgramID = glCreateProgram();

	//Log Linking Program
	glAttachShader(m_shaderProgramID, vertexShaderID);
	glAttachShader(m_shaderProgramID, fragmentShaderID);
	glLinkProgram(m_shaderProgramID);

	GLint result = GL_FALSE;
	int infoLogLenght = 0;

	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLenght);
	if (infoLogLenght > 0)
	{
		ErrorMsg.resize(infoLogLenght);
		glGetProgramInfoLog(m_shaderProgramID, infoLogLenght, NULL, &ErrorMsg[0]);
		
		//std::_Debug_message(std::wstring(ErrorMsg.begin(), ErrorMsg.end()).c_str(), __FILEW__, __LINE__);
		//Log Error Msg
		return 0;
	}

	glDetachShader(m_shaderProgramID, vertexShaderID);
	glDetachShader(m_shaderProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);


	return m_shaderProgramID;
}


GLint OGL::GetUniformLocation(const std::string &p_name)const
{
	return glGetUniformLocation(m_shaderProgramID, p_name.c_str());
}


bool OGL::ReadShader(const char* p_path, std::string &p_shaderCode)const
{
	std::string line = "";//Line of text from the stream
	std::ifstream shaderStream(p_path, std::ios::in);

	//Read vertex Shader
	if (shaderStream.is_open())
	{
		while (getline(shaderStream, line))
			p_shaderCode += "\n" + line;
		shaderStream.close();
		return true;
	}
	else
		return false;
}

bool OGL::CompileShader(const GLuint p_shaderID, const std::string &p_shaderCode, std::vector<char>p_errorMsg)const
{
	GLint result;
	int infoLogLength = 0;

	char const* vertexSourcePointer = p_shaderCode.c_str();
	glShaderSource(p_shaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(p_shaderID);

	//Check if the compilation worked
	glGetShaderiv(p_shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(p_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)//If there is a log there is a problem
	{
		p_errorMsg.resize(infoLogLength + 1);
		glGetShaderInfoLog(p_shaderID, infoLogLength, NULL, &p_errorMsg[0]);
		return false;
	}
	else
		return true;
}

OGL* OpenGL = nullptr;