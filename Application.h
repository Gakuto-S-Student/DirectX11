/*
*	Create : 2022/10/03(ŒŽ)
*		Author : Gakuto.S
*		Update : ----/10/--()
*/
#pragma once
#include "Window.h"
#include "Graphics.h"

class Application : public Window
{
public:
	Application(int width, int height, HINSTANCE hInstance);

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

public:
	Graphics* m_Graphics;

};

