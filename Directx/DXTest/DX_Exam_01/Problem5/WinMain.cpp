#include <Windows.h>
#include "Engine.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE previnstance, LPSTR lpCmdLine, int nCmdLine)
{
	Engine engine(hinstance);

	if (engine.Init() == false)
		return 0;

	return engine.Run();
}