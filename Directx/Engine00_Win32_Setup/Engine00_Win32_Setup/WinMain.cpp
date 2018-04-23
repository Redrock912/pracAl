#include <Windows.h> // 윈도우 생성용
#include "Engine.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE previnstance, // 현재는 안쓰임
	LPSTR lpCmdLine, // 콘솔창에서 parameter 넘기는 용도
	int nCmdline) // 윈도우창을 띄우는 parameter
{
	//테스트 용도
	//MessageBox(NULL, "테스트 창 ㅇㅇ","아아", MB_OK); // 앞부분은 윈도우 핸들 현재 없음. 마지막 parameter는 go to definition으로 더 많은 것들 확인 가능.

	// Engine 인스턴스 생성
	Engine engine(hinstance);

	//초기화
	if (engine.Init() == false)
	{
		return 0;
	}

	//엔진 실행
	return engine.Run();
}