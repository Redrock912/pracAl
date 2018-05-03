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
	userWidth = 1280;
	userHeight = 720;
	windowTitle = L"Problem3";
	wndStyle = WS_OVERLAPPEDWINDOW;
	appRef = this;

	// DX 멤버 변수 초기화
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



bool DXApp::InitDirectX()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hwnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 화면 크기 변경되면 갱신.
	swapDesc.BufferDesc.Width = userWidth;
	swapDesc.BufferDesc.Height = userHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	// 장치 및 스왑체인 생성

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &SwapChainRef,&DeviceRef,NULL,&DeviceContextRef);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"Couldn't create the device", L"Error", MB_OK);
		return false;
	}

	// 2D 텍스쳐 생성
	ID3D11Texture2D* BackBufferTextureRef;
	hr = SwapChainRef->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&BackBufferTextureRef);

	if (FAILED(hr))		 // E_FAIL
	{
		MessageBox(NULL, L"스왑 버퍼 생성 실패", L"오류", MB_OK);
		return false;
	}

	// 렌더 타켓 뷰 생성.
	hr = DeviceRef->CreateRenderTargetView(BackBufferTextureRef, NULL,
		&RenderTargetViewRef);

	if (FAILED(hr))		 // E_FAIL
	{
		MessageBox(NULL, L"렌더 타겟 뷰 생성 실패", L"오류", MB_OK);
		return false;
	}

	// 렌더 타켓 뷰 바인딩. 파이프 라인에 연결.
	DeviceContextRef->OMSetRenderTargets(1, &RenderTargetViewRef, NULL);

	// 리소스 해제.
	Memory::SafeRelease(BackBufferTextureRef);

	return true;
}
