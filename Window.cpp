/*
*	Create : 2022/10/03(月)
*		Author : Gakuto.S
*		Update : ----/10/--()
*/
#include "Window.h"

// コンストラクタ
Window::Window(int width, int height, LPCWSTR caption, LPCWSTR className, HINSTANCE hInstance, WNDPROC wndProc)
    :m_ClassName(className),
    m_Handle(nullptr),
    m_hInstance(hInstance)
{
    WNDCLASSEX wcex{};
    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_CLASSDC;
    wcex.lpfnWndProc    = wndProc;
    wcex.hInstance      = hInstance;
    wcex.lpszClassName  = className;
    RegisterClassEx(&wcex);

    m_Handle = CreateWindow(
        m_ClassName,
        caption,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width, height,
        nullptr,
        nullptr,
        m_hInstance,
        nullptr
    );

    // ウィンドウの表示開始
    ShowWindow(m_Handle, true);
    UpdateWindow(m_Handle);
}

// デストラクタ
Window::~Window()
{
    UnregisterClass(m_ClassName, m_hInstance);
}

// ウィンドウ状態
bool Window::Close()
{
    MSG msg;
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return true;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return false;
}
