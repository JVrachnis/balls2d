#include "Graphics.h"
Graphics::Graphics() {
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;

}
Graphics::~Graphics() {
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) 	brush->Release();
}
bool Graphics::Init(HWND windowHandle) {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,&factory);
	if (res != S_OK)return false;
	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(windowHandle,D2D1::SizeU(rect.right,rect.bottom)),&rendertarget);
	if (res != S_OK)return false;
	res =rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0 ,0), &brush);
	if (res != S_OK)return false;
	return true;
}

void Graphics::ClearScreen(float r, float g, float b) {
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}
void Graphics::DrawCircle(float y, float x, float radius, float r, float g, float b, float a) {
 	brush->SetColor(D2D1::ColorF(r,g,b,a));
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}