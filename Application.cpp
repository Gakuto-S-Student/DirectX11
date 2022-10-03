/*
*	Create : 2022/10/03(月)
*		Author : Gakuto.S
*		Update : ----/10/--()
*/
#include "Application.h"


// ウィンドウプロシージャ
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


// コンストラクタ
Application::Application(int width, int height, HINSTANCE hInstance)
	:Window(width, height, L"App", L"Sample", hInstance, WndProc)
{

}

// 初期化処理
void Application::Init()
{

}

// 終了処理
void Application::Uninit()
{
}

// 更新処理
void Application::Update()
{
}

// 描画処理
void Application::Draw()
{
}
