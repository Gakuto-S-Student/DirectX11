//==============================================================================
// Filename: Graphics.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(p)	if(p)	p->Release();	

class Graphics
{
public:
	//---------------------------------------------
	/// Get instance
	///
	/// \return	pointer on success
	//---------------------------------------------
	static Graphics* Get();

	//---------------------------------------------
	/// Initialize Directx11 
	///
	/// \param[in] ( width )
	/// \param[in] ( height )
	/// \param[in] ( hWnd )
	/// 
	/// \return	none
	//---------------------------------------------
	void Init(
		const int width,		/* [in] */
		const int height,		/* [in] */
		HWND hWnd				/* [in] */
	);
	
	//---------------------------------------------
	/// Uninitialize Directx11 
	///
	/// \return	none
	//---------------------------------------------
	void Uninit();

	//---------------------------------------------
	/// Clear screen
	///
	/// \return	none
	//---------------------------------------------
	void Clear();

	//---------------------------------------------
	/// Change buffer 
	///
	/// \return	none
	//---------------------------------------------
	void Present();

private:
	//---------------------------------------------
	/// Create device and swapchain
	///
	/// \param[in] ( width )
	/// \param[in] ( height )
	/// \param[in] ( hWnd )
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateDeviceAndSwapChain(
		const int width,    /* [in] */
		const int height,   /* [in] */
		HWND hWnd           /* [in] */
	);

	//---------------------------------------------
	/// Create render target view
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateRenderTargetView();

	//---------------------------------------------
	/// Create depth stencil view
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateDepthStencilView(
		const int width,    /* [in] */
		const int height    /* [in] */
	);

private:
	ID3D11Device*			m_device;           /// DirectX11 Device Interface
	ID3D11DeviceContext*	m_context;          /// DirectX11 DeviceContext Interface
	IDXGISwapChain*			m_swapChain;        /// DirectX11 SwapChain Interface
	ID3D11RenderTargetView* m_renderTargetView; /// DirectX11 RenderTargetView Interface
	ID3D11DepthStencilView* m_depthStencilView; /// DirectX11 DepthStencilView Interface
};

