#include "DXApp.h"

// 메시지 프로시져 우회하는데 사용하기 위해 생성
DXApp* g_pApp = NULL;


LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//g_pApp 변수가 설정됐으면 MsgProc 사용.
	if (g_pApp)
	{
		return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
	}
	//설정되지 않았다면 윈도우 기본 프로시저 함수 호출
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

DXApp::DXApp(HINSTANCE hinstance)
{
	hwnd = NULL;
	this->hinstance = hinstance;
	clientWidth = 800;
	clientHeight = 600;
	appTitle = "Engine00 - Win32 Setup";
	wndStyle = WS_OVERLAPPEDWINDOW;
	g_pApp = this;

}


DXApp::~DXApp()
{
}

int DXApp::Run()
{
	// 메인 메세지 처리
	MSG msg;
	// 0 으로 초기화
	ZeroMemory(&msg, sizeof(MSG)); // 선언 후의 쓰레기값을 초기화

	while (msg.message != WM_QUIT)
	{
		// 메세지 처리
		// GetMessage(); 메세지 들어오는 동안 잡아서 다른 작업을 안함. PeekMessage는 보면서 다른것도 처리 DX에서는 peekmessage만 사용
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// 메시지 해석
			TranslateMessage(&msg);

			// 메시지 전달
			DispatchMessage(&msg); // 해석과 전달을 동시에 하기 때문에 항상 이 둘이 같이 쓰임.

		}
		// DirectX 렌더링 루프
		else 
		{
			// Update Scene
			Update();

			//Render Scene
			Render();
		}
	}

	// 보통 이렇게 끝냄
	return (int)msg.wParam;
}

bool DXApp::Init()
{
	if (InitWindow() == false)
	{
		return false;
	}

	return true;
}

bool DXApp::InitWindow()
{
	//윈도우 클래스 값 생성/설정
	WNDCLASSEX wc;
	// 구조체 초기화
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = "WindowClass"; // 창 이름
	wc.lpszMenuName = NULL; 
	//wc.lpfnWndProc = DXApp::MsgProc;
	wc.lpfnWndProc = MainMsgProc;

	// 윈도우 클래스 등록
	if (RegisterClassEx(&wc)==false) // 초기화 실패?
	{
		return false;
	}

	// 윈도우 생성
	hwnd = CreateWindow("WindowClass", appTitle, wndStyle, 0, 0, clientWidth, clientHeight, NULL, NULL, hinstance, NULL);
	if (hwnd == NULL)
	{
		//MessageBox(NULL, "창 생성 실패", "오류", MB_OK);
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);

	return true;
}

LRESULT DXApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		//esc 키를 누르면
		if (wParam == VK_ESCAPE)
		{
			// 창 닫기 여부를 묻는 메시지 박스 생성
			if (MessageBox(NULL, "End", "The", MB_YESNO | MB_ICONQUESTION) == IDYES) 
			{

				// Yes 키 누르면 창을 삭제
				DestroyWindow(this->hwnd);
			}
		}
		return 0;

	case WM_DESTROY:
		// 명시적으로 종료
		PostQuitMessage(0);
		return 0;

	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	// default 문이 있기때문에 쓰지않음.
	//return LRESULT();
}

