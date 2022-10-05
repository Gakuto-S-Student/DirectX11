//==============================================================================
// Filename: Graphics_Camera.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

class GraphicsCamera
{
public:
	//---------------------------------------------
	/// Compute camera space for 3D 	
	/// 
	/// \param[in] ( fov )
	/// \param[in] ( aspect )
	/// \param[in] ( nearZ )
	/// \param[in] ( farZ )
	/// 
	/// \return	none
	//---------------------------------------------
	static void Set3D(
		/* [in] */  float fov,
		/* [in] */  float aspect,
		/* [in] */  float nearZ,
		/* [in] */  float farZ
	);
};

