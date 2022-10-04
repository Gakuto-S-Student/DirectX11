//==============================================================================
// Filename: Application.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "Application_Window.h"


class GraphicsCube;

class Application : public ApplicationWindow
{
public:
	//---------------------------------------------
	/// Constructor 
	///
	/// \param[in] ( width )
	/// \param[in] ( height )
	/// \param[in] ( hInstance )
	/// 
	/// \return	none
	//---------------------------------------------
	Application(
		const int width,	/* [in] */
		const int height,   /* [in] */
		HINSTANCE hInstance /* [in] */
	);

	//---------------------------------------------
	/// Initilize application 
	///
	/// \return	none
	//---------------------------------------------
	void Init();

	//---------------------------------------------
	/// Uninitilize application 
	///
	/// \return	none
	//---------------------------------------------
	void Uninit();

	//---------------------------------------------
	/// Update 
	///
	/// \return	none
	//---------------------------------------------
	void Update();

	//---------------------------------------------
	/// Draw 
	///
	/// \return	none
	//---------------------------------------------
	void Draw();

	int m_ScreenW;	/// ウィンドウ幅
	int m_ScreenH;	/// ウィンドウ高さ

private:
	GraphicsCube* m_cube;	/// 
};

