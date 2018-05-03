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
	userWidth = 1280;
	userHeight = 720;
	windowTitle = L"Problem2";
	wndStyle = WS_OVERLAPPEDWINDOW;
	appRef = this;

	// DX ��� ���� �ʱ�ȭ
	DeviceRef = NULL;
	DeviceContextRef = NULL;
	SwapChainRef = NULL;
	RenderTargetViewRef = NULL;
}

DXApp::~DXApp()
{
	Memory::SafeRelease(DeviceRef);
	Memory::SafeRelease(DeviceContextRef);
	Memory::SafeRelease(SwapChainRef);
	Memory::SafeRelease(RenderTargetViewRef);
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

	if (InitDirectX() == false)
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



bool DXApp::InitDirectX()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hwnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ȭ�� ũ�� ����Ǹ� ����.
	swapDesc.BufferDesc.Width = userWidth;
	swapDesc.BufferDesc.Height = userHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	// ��ġ �� ����ü�� ����

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &SwapChainRef,&DeviceRef,NULL,&DeviceContextRef);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"Couldn't create the device", L"Error", MB_OK);
		return false;
	}

	// 2D �ؽ��� ����
	ID3D11Texture2D* BackBufferTextureRef;
	hr = SwapChainRef->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&BackBufferTextureRef);

	if (FAILED(hr))		 // E_FAIL
	{
		MessageBox(NULL, L"���� ���� ���� ����", L"����", MB_OK);
		return false;
	}

	// ���� Ÿ�� �� ����.
	hr = DeviceRef->CreateRenderTargetView(BackBufferTextureRef, NULL,
		&RenderTargetViewRef);

	if (FAILED(hr))		 // E_FAIL
	{
		MessageBox(NULL, L"���� Ÿ�� �� ���� ����", L"����", MB_OK);
		return false;
	}

	// ���� Ÿ�� �� ���ε�. ������ ���ο� ����.
	DeviceContextRef->OMSetRenderTargets(1, &RenderTargetViewRef, NULL);

	// ���ҽ� ����.
	Memory::SafeRelease(BackBufferTextureRef);

	return true;
}
