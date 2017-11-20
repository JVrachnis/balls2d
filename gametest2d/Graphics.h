#pragma once
#include <Windows.h>
#include <d2d1.h>
class Graphics
{
public:
	Graphics();
	~Graphics();
	bool Init(HWND windowHandle);
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float y, float x, float radius, float r, float g, float b, float a);
private:
	ID2D1SolidColorBrush* brush;
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
};