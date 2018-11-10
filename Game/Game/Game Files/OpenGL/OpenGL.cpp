#include "OpenGL.h"

OGL* OGL::m_instance = nullptr;

OGL::OGL()
	:m_clearColor(Color()), m_clearFlag(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
{}


OGL* OGL::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew OGL();
	return m_instance;
}


void OGL::Enable(HWND p_handle, const Color &p_clearColor, const glm::vec2 &p_viewSize)
{
	m_clearColor = p_clearColor;

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

	//**********Combine*****************
	int format = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, format, &pfd);


	m_hglrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hglrc);

	if (glewInit() != GLEW_OK)
		ERR_MSG("Glew init failure");

	glViewport(0, 0, static_cast<GLsizei>(p_viewSize.x), static_cast<GLsizei>(p_viewSize.y));

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

GLuint OGL::LoadShader(const char* p_vPath, const char* p_fPath)const
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
	vertexShaderID = CompileShader(fragmentShaderCode, ErrorMsg);
	if (vertexShaderID == 0)//Compile error
	{
		ERR_MSG("Error Compiling Vertex shader");
		//Log ErrorMsg
		return 0;
	}
	//Log Compiling Fragment Shader
	fragmentShaderID = CompileShader(fragmentShaderCode, ErrorMsg);
	if (fragmentShaderID == 0)//Compile error
	{
		ERR_MSG("Error Compiling Fragment shader");
		//Log ErrorMsg
		return 0;
	}

	GLuint ProgramID = glCreateProgram();
	
	//Log Linking Program
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);

	GLint result = GL_FALSE;
	int infoLogLenght = 0;

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLenght);
	if (infoLogLenght > 0)
	{
		glGetProgramInfoLog(ProgramID, infoLogLenght, NULL, &ErrorMsg[0]);
		//Log Error Msg
		return 0;
	}

	glDetachShader(ProgramID, vertexShaderID);
	glDetachShader(ProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ProgramID;
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

GLuint OGL::CompileShader(const std::string &p_shaderCode, std::vector<char>p_errorMsg)const
{
	GLuint shaderID;
	GLint result = GL_FALSE;
	int infoLogLength = 0;

	char const* vertexSourcePointer = p_shaderCode.c_str();
	glShaderSource(shaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(shaderID);

	//Check if the compilation worked
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)//If there is a log there is a problem
	{
		p_errorMsg.resize(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &p_errorMsg[0]);
		return 0;
	}
	else
		return shaderID;
}

OGL* OpenGL = nullptr;