//==============================================================================
// Filename: Application_Window.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

#include <Windows.h>

class ApplicationWindow
{
public:
	//---------------------------------------------
	/// Get window status 
	///
	/// \return	true on close window
	//---------------------------------------------
	bool Close();
	
	//---------------------------------------------
	/// Destructor 
	///
	/// \return	none
	//---------------------------------------------
	virtual ~ApplicationWindow();


protected:
	ApplicationWindow() = delete;
	ApplicationWindow(const ApplicationWindow&) = delete;

	//---------------------------------------------
	/// Constructor 
	///
	/// \param[in] ( width )
	/// \param[in] ( height )
	/// \param[in] ( caption )
	/// \param[in] ( className )
	/// \param[in] ( hInstance )
	/// \param[in] ( wndProc )  WNDPROC
	/// 
	/// \return	none
	//---------------------------------------------
	ApplicationWindow(
		int width,
		int height,
		LPCWSTR caption,
		LPCWSTR className,
		HINSTANCE hInstance,
		WNDPROC wndProc
	);

	HWND m_windowHandle; /// �E�B���h�E�n���h��

private:
	LPCWSTR		m_className;    /// �E�B���h�E�̃N���X��
	HINSTANCE	m_hInstance;    /// �C���X�^���X�n���h��
};

