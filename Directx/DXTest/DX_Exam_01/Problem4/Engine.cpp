#include "Engine.h"

Engine::Engine(HINSTANCE hinstance) :DXApp(hinstance)
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	// dx 초기화
	if (DXApp::Init() == false)
		return false;
	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{
	// 배경 지우기. (백버퍼 지우기).
	float color[4] = { 1.0f, 0.2f, 0.2f, 1.0f };
	DeviceContextRef->ClearRenderTargetView(RenderTargetViewRef, color);


	// 정점 그리기.
	DeviceContextRef->Draw(3, 0);

	// 버퍼 교체. (백버퍼 <-> 프론트버퍼).
	SwapChainRef->Present(0, 0);
	

}
