//==============================================================================
// Filename: Graphics.h
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
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
	/// Get ID3D11Device
	///
	/// \return	pointer on success
	//---------------------------------------------
	ID3D11Device* Device();

	//---------------------------------------------
	/// Get ID3D11DeviceContext
	///
	/// \return	pointer on success
	//---------------------------------------------
	ID3D11DeviceContext* Context();

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

	//---------------------------------------------
	/// Set model matrix
	///
	/// \param[in] ( model )
	/// 
	/// \return	none
	//---------------------------------------------
	void SetModelMatrix(const DirectX::XMMATRIX model);

	//---------------------------------------------
	/// Set view matrix
	///
	/// \param[in] ( view )
	/// 
	/// \return	none
	//---------------------------------------------
	void SetViewMatrix(const DirectX::XMMATRIX view);

	//---------------------------------------------
	/// Set projection matrix
	///
	/// \param[in] ( projection )
	/// 
	/// \return	none
	//---------------------------------------------
	void SetProjectionMatrix(const DirectX::XMMATRIX projection);


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
	/// \param[in] ( width )
	/// \param[in] ( height )
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateDepthStencilView(
		const int width,    /* [in] */
		const int height    /* [in] */
	);

	//---------------------------------------------
	/// Create rasterizer state
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateRasterizerState();

	//---------------------------------------------
	/// Create blend state
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateBlendState();

	//---------------------------------------------
	/// Create depth stencil state
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateDepthStencilState();
	
	//---------------------------------------------
	/// Create sampler state
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateSamplerState();

	//---------------------------------------------
	/// Create constant buffers
	/// 
	/// \return	none
	//---------------------------------------------
	void CreateConstantBuffers();

	//---------------------------------------------
	/// Set viewport
	/// 
	/// \param[in] ( width )
	/// \param[in] ( height )
	/// 
	/// \return	none
	//---------------------------------------------
	void SetViewport(
		const int width,  /* [in] */
		const int height  /* [in] */
	);

private:
	ID3D11Device*			    m_device;               /// DirectX11 Device Interface
	ID3D11DeviceContext*	    m_context;              /// DirectX11 DeviceContext Interface
	IDXGISwapChain*			    m_swapChain;            /// DirectX11 SwapChain Interface
	ID3D11RenderTargetView*     m_renderTargetView;     /// DirectX11 RenderTargetView Interface
	ID3D11DepthStencilView*     m_depthStencilView;     /// DirectX11 DepthStencilView Interface
	ID3D11RasterizerState*      m_rasterizerState;      /// DirectX11 RasterizerState Interface
	ID3D11BlendState*           m_blendState;           /// DirectX11 BlendState Interface
	ID3D11DepthStencilState*    m_depthStencilState;    /// DirectX11 DepthStencilState Interface
	ID3D11SamplerState*         m_samplerState;         /// DirectX11 SamplerState Interface
	ID3D11Buffer*               m_modelMatrix;          /// DirectX11 The buffer is model matrix send to vertex buffer 
	ID3D11Buffer*               m_viewMatrix;           /// DirectX11 The buffer is view matrix send to vertex buffer
	ID3D11Buffer*               m_projectionMatrix;     /// DirectX11 The buffer is projection matrix send to vertex buffer
};

