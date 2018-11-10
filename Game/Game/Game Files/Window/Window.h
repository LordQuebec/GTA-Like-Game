#pragma once

#include <Windows.h>

#include <tchar.h>

#include "../Debug/Debug.h"
#include "../GameObject/GameObject.h"
#include "../OpenGL/OpenGL.h"
#include "../glm/vec2.hpp"


class WindowMgr : public GameObject
{
private:
	WindowMgr();
	static WindowMgr* m_instance;

	std::wstring m_windowName;

	glm::vec2 m_pos;
	glm::vec2 m_size;
	glm::vec2 m_center;
	float m_ratio;

	HWND m_handle;
	WNDCLASSEX m_wcex;

	bool m_focus;
	bool m_moved;
	bool m_resized;
	bool m_exist;

	//void LoadConfig
	void UpdatePos();
	void UpdateSize();

protected:
	void FrameStartUpdate();

public:
	static WindowMgr* CreateInstance();
	static WindowMgr* GetInstance() { return m_instance; }

	int Create(std::wstring &name, HINSTANCE, WNDPROC, int nCmdShow);

	glm::vec2 GetPos()const { return m_pos; }
	glm::vec2 GetSize()const { return m_size; }
	glm::vec2 GetCenter()const { return m_center; }
	float GetRatio()const { return m_ratio; }

	void SetPos(const glm::vec2 &pos);
	void SetPos(const float X, const float Y);

	void SetSize(const glm::vec2 &size);
	void SetSize(const float Width, const float Height);

	bool Moved()const { return m_moved; }
	bool Resized()const { return m_resized; }
	bool HasFocus()const { return m_focus; }

	void Show(bool show) { ShowWindow(m_handle, static_cast<int>(show) * SW_SHOW); }
	void Show(int cmd) { ShowWindow(m_handle, cmd); }
	void Show() { ShowWindow(m_handle, SW_SHOW); }
	void Hide() { ShowWindow(m_handle, SW_HIDE); }
	void SetFocus(const bool focus) { m_focus = focus; }

	const HWND GetHandle()const { return m_handle; }

	~WindowMgr();
};

extern WindowMgr*Window;

#define ForwardWinPos do{Window->SetPos(LOWROD(lParam), HIWORD(lParam));} while(0)
#define ForwardWinResize do{Window->SetSize(LWORD(lParam), HIWORD(lParam));} while (0)