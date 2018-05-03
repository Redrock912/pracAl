#include "DXApp.h"

DXApp* appRef = NULL;


LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// appRef 변수가 설정됐으면 MsgProc 사용.
	if (appRef) return appRef->MsgProc(hwnd, msg, wParam, lParam);

	// 설정되지 않으면 윈도우 기본 프로시저 함수 호출.
	else return DefWindowProc(hwnd, msg, wParam, lParam);
}
DXApp::DXApp(HINSTANCE hinstance)
{
	// 변수 초기화
	hwnd = NULL;
	this->hinstance = hinstance;
	userWidth = 800;
	userHeight = 600;
	windowTitle = L"Problem1";
	wndStyle = WS_OVERLAPPEDWINDOW;
	appRef = this;
}

DXApp::~DXApp()
{
}

int DXApp::Run()
{
	// 메시지 처리
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// DXApp 렌더링 루프
		else
		{
			Update();
			Render();
		}
	}
	return (int)msg.wParam;
}

bool DXApp::Init()
{
	// 윈도우 초기화
	if (InitWindow() == false)
		return false;

	return true;
}

void DXApp::Update()
{
}

void DXApp::Render()
{
}

LRESULT DXApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam = VK_ESCAPE)
		{
			// 창 닫기 여부를 물음
			if (MessageBox(NULL, L"would you like to end?", L"End", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(this->hwnd);
			}
		}
		return 0;
		// 창 삭제시 실행
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

bool DXApp::InitWindow()
{
	// 윈도우 클래스 값 생성/설정.
	WNDCLASSEX wc;
	// 구조체 초기화.
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = L"WC";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = MainMsgProc;

	// 윈도우 클래스 등록.
	if (RegisterClassEx(&wc) == false)
		return false;

	// 윈도우 생성.
	hwnd = CreateWindow(L"WC", windowTitle,
		wndStyle, 0, 0, userWidth, userHeight,
		NULL, NULL, hinstance, NULL);
	// 생성 실패하면 종료.
	if (hwnd == NULL)
	{
		return false;
	}

	// 창 띄우기.
	ShowWindow(hwnd, SW_SHOW);

	return true;
}
