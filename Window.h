/*
*	Create : 2022/10/03(ŒŽ)
*		Author : Gakuto.S
*		Update : ----/10/--()
*/
#pragma once
#include <Windows.h>

class Window
{
protected:
	Window() = delete;
	Window(const Window&) = delete;
	Window(
		int width, int height,
		LPCWSTR caption,
		LPCWSTR className,
		HINSTANCE hInstance,
		WNDPROC wndProc
	);

	~Window();

public:
	bool Close();

protected:
	HWND m_Handle;

private:
	LPCWSTR		m_ClassName;
	HINSTANCE	m_hInstance;
};

