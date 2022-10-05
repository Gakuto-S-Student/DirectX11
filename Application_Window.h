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
		/* [in] */  int width,
		/* [in] */  int height,
		/* [in] */  LPCWSTR caption,
		/* [in] */  LPCWSTR className,
		/* [in] */  HINSTANCE hInstance,
		/* [in] */  WNDPROC wndProc
	);

	//--------------------------------------------------------------------------
	HWND m_windowHandle;
	//--------------------------------------------------------------------------

	/// <summary>
	/// HWND m_windowHandle;   ウィンドウハンドル
	/// </summary>
	

private:
	//--------------------------------------------------------------------------
	LPCWSTR		m_className;
	HINSTANCE	m_hInstance;
	//--------------------------------------------------------------------------

	/// <summary>
	/// LPCWSTR		m_className;   ウィンドウのクラスネーム
	/// HINSTANCE	m_hInstance;   インスタンスハンドル
	/// </summary>
	
};

