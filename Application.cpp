//==============================================================================
// Filename: Application.cpp
// Description:
// Copyright (C) 2022 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Graphics.h"
#include "Graphics_Cube.h"

#include "Application.h"

int Application::m_ScreenW = 0;
int Application::m_ScreenH = 0;


// �E�B���h�E�v���V�[�W��
static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


// �R���X�g���N�^
Application::Application(const int width, const int height, HINSTANCE hInstance)
	:ApplicationWindow(width, height, L"App", L"Sample", hInstance, WndProc)
{
	m_ScreenW = width;
	m_ScreenH = height;
}

// ����������
void Application::Init()
{
	Graphics::Get()->Init(m_ScreenW, m_ScreenH, m_windowHandle);

	m_cube = new GraphicsCube();
	m_cube->Init();
}

// �I������
void Application::Uninit()
{
	m_cube->Uninit();
	delete m_cube;

	Graphics::Get()->Uninit();
}

// �X�V����
void Application::Update()
{
}

// �`�揈��
void Application::Draw()
{
	Graphics::Get()->Clear();

	m_cube->Draw();

	Graphics::Get()->Present();
}
