/*
*	Create : 2022/10/03(��)
*		Author : Gakuto.S
*		Update : ----/10/--()
*/
#include "Application.h"


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
Application::Application(int width, int height, HINSTANCE hInstance)
	:Window(width, height, L"App", L"Sample", hInstance, WndProc)
{

}

// ����������
void Application::Init()
{

}

// �I������
void Application::Uninit()
{
}

// �X�V����
void Application::Update()
{
}

// �`�揈��
void Application::Draw()
{
}
