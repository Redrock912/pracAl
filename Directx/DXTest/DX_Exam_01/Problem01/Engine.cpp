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
}
