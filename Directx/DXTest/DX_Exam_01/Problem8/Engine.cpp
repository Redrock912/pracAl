#include "Engine.h"

Engine::Engine(HINSTANCE hinstance) :DXApp(hinstance)
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	// dx �ʱ�ȭ
	if (DXApp::Init() == false)
		return false;
	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{
	// ��� �����. (����� �����).
	float color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	DeviceContextRef->ClearRenderTargetView(RenderTargetViewRef, color);

	// ���� �׸���.
	DeviceContextRef->DrawIndexed(nIndices, 0, 0);

	// ���� ��ü. (����� <-> ����Ʈ����).
	SwapChainRef->Present(0, 0);
	

}
