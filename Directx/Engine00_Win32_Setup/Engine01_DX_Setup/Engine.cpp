#include "Engine.h"



Engine::Engine(HINSTANCE hinstance) : DXApp(hinstance) // DXApp 에서 생성자를 받아서 초기화
{
}


Engine::~Engine()
{
}

bool Engine::Init()
{
	if (DXApp::Init() == false)
	{
		return false;
	}

	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{
}
