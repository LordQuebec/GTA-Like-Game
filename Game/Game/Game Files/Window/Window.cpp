#include "Window.h"

using namespace std;

WindowMgr* WindowMgr::m_instance = nullptr;


WindowMgr::WindowMgr()
	:GameObject(this, "Window"), m_handle(NULL), m_windowName(L"Game")
{}

WindowMgr* WindowMgr::CreateInstance()
{
	if (!m_instance)
		m_instance = sNew WindowMgr();
	return m_instance;
}


int WindowMgr::Create(wstring &p_name, int sizeX, int sizeY, HINSTANCE p_hInstance, WNDPROC p_wndProc, int p_nCmdShow)
{
	m_windowName = p_name;
	ZeroMemory(&m_wcex, sizeof(m_wcex));

	m_wcex.cbSize = sizeof(m_wcex);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW; // | CS_DROPSHADOW
	m_wcex.lpfnWndProc = p_wndProc;
	m_wcex.hInstance = p_hInstance;
	m_wcex.hIcon = LoadIcon(p_hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	m_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wcex.lpszClassName = (LPCWSTR)"WinClass";

	//Check class registration succes
	if (!RegisterClassEx(&m_wcex))
	{
		ERR_MSG("Call to RegisterClassEx Failed");
		return 1;//Exit program
	}

	//Create Window
	m_handle = CreateWindowEx(
		NULL,
		m_wcex.lpszClassName,
		m_windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		sizeX, sizeY,
		NULL, NULL,
		p_hInstance,
		NULL);

	//Check window creation succes
	if (!m_handle)
	{
		ERR_MSG("Call to CreateWindow failed");
		return 1;//Exit
	}
	//ShowWindow(m_handle, p_nCmdShow);

	return 0;
}

#pragma region Pos & Size

void WindowMgr::SetPos(const glm::vec2 &p_pos)
{
	m_pos = p_pos;
	UpdatePos();
}

void WindowMgr::SetPos(const float p_x, const float p_y)
{
	m_pos.x = p_x;
	m_pos.y = p_y;
	UpdatePos();
}

void WindowMgr::SetSize(const glm::vec2 &p_size)
{
	m_size = p_size;
	UpdateSize();
}

void WindowMgr::SetSize(const float p_width, const float p_height)
{
	m_size.x = p_width;
	m_size.y = p_height;
	UpdateSize();
}


void WindowMgr::UpdatePos()
{
	m_moved = true;
	m_center = (m_pos + m_size) / 2.0f;
}

void WindowMgr::UpdateSize()
{
	m_resized = true;
	m_center = (m_pos + m_size) / 2.0f;
	m_ratio = m_size.x / m_size.y;
	OpenGL->ResizeViewPort(m_size);
}

#pragma endregion

void WindowMgr::FrameStartUpdate()
{
	m_moved = m_resized = false;
}


WindowMgr::~WindowMgr()
{
	if (!DestroyWindow(m_handle))
		ERR_MSG("Window destruction error");
	if (!UnregisterClass(m_wcex.lpszClassName, m_wcex.hInstance))
		ERR_MSG("Window class unregister error");

	m_instance = nullptr;
}

WindowMgr* Window = nullptr;