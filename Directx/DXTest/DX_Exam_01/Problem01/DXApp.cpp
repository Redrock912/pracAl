#include "DXApp.h"

DXApp* appRef = NULL;


LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// appRef ������ ���������� MsgProc ���.
	if (appRef) return appRef->MsgProc(hwnd, msg, wParam, lParam);

	// �������� ������ ������ �⺻ ���ν��� �Լ� ȣ��.
	else return DefWindowProc(hwnd, msg, wParam, lParam);
}
DXApp::DXApp(HINSTANCE hinstance)
{
	// ���� �ʱ�ȭ
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
	// �޽��� ó��
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// DXApp ������ ����
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
	// ������ �ʱ�ȭ
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
			// â �ݱ� ���θ� ����
			if (MessageBox(NULL, L"would you like to end?", L"End", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(this->hwnd);
			}
		}
		return 0;
		// â ������ ����
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

bool DXApp::InitWindow()
{
	// ������ Ŭ���� �� ����/����.
	WNDCLASSEX wc;
	// ����ü �ʱ�ȭ.
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

	// ������ Ŭ���� ���.
	if (RegisterClassEx(&wc) == false)
		return false;

	// ������ ����.
	hwnd = CreateWindow(L"WC", windowTitle,
		wndStyle, 0, 0, userWidth, userHeight,
		NULL, NULL, hinstance, NULL);
	// ���� �����ϸ� ����.
	if (hwnd == NULL)
	{
		return false;
	}

	// â ����.
	ShowWindow(hwnd, SW_SHOW);

	return true;
}
