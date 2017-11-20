#include<Windows.h>
#include"Graphics.h"
#include <iostream>
#include <array>
#include <list>
#include <math.h>
#include"Ball.h"
//const float WINDOW_SIZE_X = 800;
//const float WINDOW_SIZE_Y = 800;
std::list<Ball*> balls;
Graphics* graphics;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR cmd,int nCmdShow) 
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowclass);

	RECT rect = {0,0,(long)WINDOW_SIZE_X,(long)WINDOW_SIZE_Y };
	AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,false,WS_EX_OVERLAPPEDWINDOW);
	HWND windowhanle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"MainWindow","Test!!",WS_OVERLAPPEDWINDOW,0,0,rect.right-rect.left,rect.bottom-rect.top,NULL,NULL,hInstance,0);
	if (!windowhanle)return -1;
	ShowWindow(windowhanle, nCmdShow);
	graphics = new Graphics();
	if (!graphics->Init(windowhanle)) {
		delete graphics;
		return -1;
	}
	std::list<Ball*> ballsall;

	int wait=0,numBalls=0;
	MSG message;
	message.message = WM_NULL;
	while ( message.message !=WM_QUIT)
	{
		if(PeekMessage(&message,NULL,0,0,PM_REMOVE)) DispatchMessage(&message);
		else
		{
			if (wait==60 && numBalls<50)
			{
				Ball* ball = new Ball(graphics ,50, 50);
				balls.push_back(ball);
				wait = 0;
				numBalls++;
			}
			graphics->BeginDraw();
			graphics->ClearScreen(0.9f,0.8f,0.9f);
			for each(Ball* ball in balls) {
				ball->UpDate(balls);
				ball->Render();
			}
			graphics->EndDraw();
			wait++;
		}
	}
	delete graphics;
	return 0;
}/*
bool foundL(std::list<Ball*> l,Ball* ball) {
	return std::find(l.begin(), l.end(), ball) != l.end();
}

std::array<std::array<std::list<Ball*>, 20>, 20> ballhandler(std::list<Ball*> balls){
	std::array<std::array<std::list<Ball*>, 20>, 20> otherballs;
	for each(Ball* ball in balls)
	{
		otherballs[0][0].push_back(ball);
		
		int i, j;
		if (((int)(ball->X / 40) < 20) && ((int)(ball->X / 40) >= 0)) i = (int)(ball->X / 40);
		else if ((int)(ball->X / 40) >= 20) i = 19;
		else if ((int)(ball->X / 40) < 0) i = 0;
		if (((int)(ball->Y / 40) < 20) && ((int)(ball->Y / 40) >= 0)) j = (int)(ball->Y / 40);
		else if ((int)(ball->Y / 40) >= 20) j = 19;
		else if ((int)(ball->Y / 40) < 0) j = 0;
		//for X 
		otherballs[i][j].push_back(ball);
		
		if ((i + 1 < 20) && (j + 1 < 20)) {
			otherballs[i + 1][j + 1].push_back(ball);
		}
		if ((i - 1 > 0) && (j - 1 > 0)) {
			otherballs[i - 1][j - 1].push_back(ball);
		}

		if (i + 1 < 20)
		{

			otherballs[i + 1][j].push_back(ball);

		}
		if (i - 1 > 0)
		{

			otherballs[i - 1][j].push_back(ball);
		}
		//for Y
		if (j + 1 < 20)
		{
			otherballs[i][j + 1].push_back(ball);

		}
		if (j - 1 > 0)
		{
			otherballs[i][j - 1].push_back(ball);
		}
	}
		
	//otherballs;
	return otherballs;
}
*/