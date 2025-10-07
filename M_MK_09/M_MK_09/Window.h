#pragma once
#include <Windows.h>

LRESULT CALLBACK NzWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Window() = default;
	virtual ~Window() = default;

	bool Create(const wchar_t* className, const wchar_t* windowName, int width, int height);
	void Delete();
	void* Gethandle() const { return m_hWnd; }

	const int& GetWidth() const { return w_width; }
	const int& GetHeight() const { return w_height; }

	

protected:
	friend LRESULT CALLBACK NzWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HWND m_hWnd = HWND();
	int w_width = 0;
	int w_height = 0;

	//이동 복사 대입 복사 대입 금! 
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;
};