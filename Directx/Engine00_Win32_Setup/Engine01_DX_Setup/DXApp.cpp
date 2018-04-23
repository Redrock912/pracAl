#include "DXApp.h"

// �޽��� ���ν��� ��ȸ�ϴµ� ����ϱ� ���� ����
DXApp* g_pApp = NULL;


LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//g_pApp ������ ���������� MsgProc ���.
	if (g_pApp)
	{
		return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
	}
	//�������� �ʾҴٸ� ������ �⺻ ���ν��� �Լ� ȣ��
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
	// ���� �޼��� ó��
	MSG msg;
	// 0 ���� �ʱ�ȭ
	ZeroMemory(&msg, sizeof(MSG)); // ���� ���� �����Ⱚ�� �ʱ�ȭ

	while (msg.message != WM_QUIT)
	{
		// �޼��� ó��
		// GetMessage(); �޼��� ������ ���� ��Ƽ� �ٸ� �۾��� ����. PeekMessage�� ���鼭 �ٸ��͵� ó�� DX������ peekmessage�� ���
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// �޽��� �ؼ�
			TranslateMessage(&msg);

			// �޽��� ����
			DispatchMessage(&msg); // �ؼ��� ������ ���ÿ� �ϱ� ������ �׻� �� ���� ���� ����.

		}
		// DirectX ������ ����
		else 
		{
			// Update Scene
			Update();

			//Render Scene
			Render();
		}
	}

	// ���� �̷��� ����
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
	//������ Ŭ���� �� ����/����
	WNDCLASSEX wc;
	// ����ü �ʱ�ȭ
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = "WindowClass"; // â �̸�
	wc.lpszMenuName = NULL; 
	//wc.lpfnWndProc = DXApp::MsgProc;
	wc.lpfnWndProc = MainMsgProc;

	// ������ Ŭ���� ���
	if (RegisterClassEx(&wc)==false) // �ʱ�ȭ ����?
	{
		return false;
	}

	// ������ ����
	hwnd = CreateWindow("WindowClass", appTitle, wndStyle, 0, 0, clientWidth, clientHeight, NULL, NULL, hinstance, NULL);
	if (hwnd == NULL)
	{
		//MessageBox(NULL, "â ���� ����", "����", MB_OK);
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
		//esc Ű�� ������
		if (wParam == VK_ESCAPE)
		{
			// â �ݱ� ���θ� ���� �޽��� �ڽ� ����
			if (MessageBox(NULL, "End", "The", MB_YESNO | MB_ICONQUESTION) == IDYES) 
			{

				// Yes Ű ������ â�� ����
				DestroyWindow(this->hwnd);
			}
		}
		return 0;

	case WM_DESTROY:
		// ��������� ����
		PostQuitMessage(0);
		return 0;

	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	// default ���� �ֱ⶧���� ��������.
	//return LRESULT();
}

