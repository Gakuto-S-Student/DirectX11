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
		/* [in] */  const int width,	
		/* [in] */  const int height,   
		/* [in] */  HINSTANCE hInstance 
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

	//--------------------------------------------------------------------------
	int m_ScreenW;
	int m_ScreenH;
	//--------------------------------------------------------------------------

	/// <summary>
	/// int m_ScreenW; �E�B���h�E��
	/// int m_ScreenH; �E�B���h�E����
	/// </summary>

private:
	//--------------------------------------------------------------------------
	GraphicsCube* m_cube;
	//--------------------------------------------------------------------------

	/// <summary>
	/// GraphicsCube* m_cube; �L���[�u�N���X 
	/// </summary>
	
};

