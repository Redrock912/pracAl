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
	windowTitle = L"Problem9";
	wndStyle = WS_OVERLAPPEDWINDOW;
	appRef = this;

	// DX 멤버 변수 초기화
	DeviceRef = NULL;
	DeviceContextRef = NULL;
	SwapChainRef = NULL;
	RenderTargetViewRef = NULL;

	vertexBuffer = NULL;
	vertexShader = NULL;
	vertexShaderBuffer = NULL;
	pixelShader = NULL;
	pixelShaderBuffer = NULL;
	vertexInputLayout = NULL;

	indexBuffer = NULL;

}

DXApp::~DXApp()
{
	Memory::SafeRelease(DeviceRef);
	Memory::SafeRelease(DeviceContextRef);
	Memory::SafeRelease(SwapChainRef);
	Memory::SafeRelease(RenderTargetViewRef);

	Memory::SafeRelease(vertexBuffer);
	Memory::SafeRelease(vertexShader);
	Memory::SafeRelease(pixelShader);
	Memory::SafeRelease(vertexShaderBuffer);
	Memory::SafeRelease(pixelShaderBuffer);
	Memory::SafeRelease(vertexInputLayout);

	Memory::SafeRelease(indexBuffer);

	Memory::SafeRelease(cbBuffer);
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

	if (InitScene() == false)
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

bool DXApp::InitScene()
{
	// 쉐이더 컴파일.
	HRESULT hr;
	// 정점 쉐이더 컴파일.
	hr = D3DX11CompileFromFile(L"Effects.fx", NULL, NULL, "VS_Main", "vs_5_0", NULL, NULL, NULL, &vertexShaderBuffer, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"컴파일 실패1", L"오류", MB_OK);
		return false;
	}

	// 정점 쉐이더 오브젝트 생성.
	DeviceRef->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);

	// 정점 쉐이더 설정.(바인딩).
	DeviceContextRef->VSSetShader(vertexShader, NULL, NULL);

	// 픽셀 쉐이더.
	hr = D3DX11CompileFromFile(L"Effects.fx", NULL, NULL, "PS_Main",
		"ps_5_0", NULL, NULL, NULL, &pixelShaderBuffer, NULL, NULL);

	// 픽셀 쉐이더 오브젝트 생성.
	DeviceRef->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

	// 픽셀 쉐이더 바인딩.
	DeviceContextRef->PSSetShader(pixelShader, NULL, NULL);

	// 정점 만들기.
	Vertex vertices[] =
	{
		// Front Face
		Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

		// Back Face
		Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
		Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
		Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

		// Top Face
		Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
		Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
		Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

		// Bottom Face
		Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
		Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

		// Left Face
		Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
		Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
		Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

		// Right Face
		Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
		Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
	};

	DWORD indices[] =
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	nIndices = ARRAYSIZE(indices);
	// sizeof(vertices) / sizeof(vertices[0]);
	// 버텍스 버퍼 서술자(Descriptor).
	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	// 서브 리소스 생성.
	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = vertices;

	// 정점 버퍼 생성.
	DeviceRef->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);

	// 인덱스 버퍼 서술자(Descriptor).
	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.ByteWidth = sizeof(DWORD) * ARRAYSIZE(indices);
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	// 서브 리소스 생성.
	D3D11_SUBRESOURCE_DATA ibData;
	ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibData.pSysMem = indices;

	// 인덱스 버퍼 생성.
	DeviceRef->CreateBuffer(&ibDesc, &ibData, &indexBuffer);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// 정점 버퍼 바인딩.
	DeviceContextRef->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	DeviceContextRef->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// 입력 레이아웃.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// 입력 레이아웃 생성.
	DeviceRef->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &vertexInputLayout);

	// 입력 레이아웃 바인딩.
	DeviceContextRef->IASetInputLayout(vertexInputLayout);

	// 기본 토폴로지 설정 (TRIANGLELIST로 설정).
	DeviceContextRef->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 뷰포트 정보 설정.
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = userWidth;
	viewport.Height = userHeight;

	// 뷰포트 설정.
	DeviceContextRef->RSSetViewports(1, &viewport);

	// World x View x Projection;
	// 월드 행렬. (위치/회전/스케일).
	world = XMMatrixIdentity();

	// 카메라 위치.
	cameraPos = XMVectorSet(3.0f, 1.0f, -5.0f, 0.0f);

	// 카메라가 바라보는 위치.
	cameraTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	// 카메라 위 방향.
	cameraUp = XMVectorSet(5.0f, 2.0f, 0.0f, 0.0f);

	// 뷰 행렬.
	view = XMMatrixLookAtLH(cameraPos, cameraTarget, cameraUp);

	// 시야각.
	float fovY = 75.0f * 3.14 / 180.0f;

	// 투영 행렬.
	projection = XMMatrixPerspectiveFovLH(fovY, (float)userWidth / userHeight,
		1.0f, 1000.0f);

	// 상수 버퍼 데이터 설정 및 파이프라인 바인딩.
	// 전치행렬을 만들어서 데이터 채우기.
	// DX는 행우선 / HLSL은 열우선.
	CBPerObject data;
	data.world = XMMatrixTranspose(world);
	data.view = XMMatrixTranspose(view);
	data.projection = XMMatrixTranspose(projection);

	// 버퍼 디스크립터.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = sizeof(CBPerObject);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	// 서브 리소스 생성.
	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &data;

	// 상수 버퍼 생성.
	hr = DeviceRef->CreateBuffer(&cbDesc, &cbData, &cbBuffer);

	// 파이프라인에 바인딩.
	DeviceContextRef->VSSetConstantBuffers(0, 1, &cbBuffer);

	// 텍스처 로드(샘플러 초기화).
	if (!InitTexture())
		return false;

	// 텍스처 바인딩.
	DeviceContextRef->PSSetShaderResources(0, 1, &TextureRef);
	// 샘플러 스테이트 바인딩.
	DeviceContextRef->PSSetSamplers(0, 1, &TextureSamplerStateRef);

	return true;
}

bool DXApp::InitTexture()
{
	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFile(DeviceRef, L"mario.jpg", NULL, NULL, &TextureRef, NULL);

	if (FAILED(hr))
		return false;	

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// 샘플러 상태(State) 생성.
	hr = DeviceRef->CreateSamplerState(&samplerDesc, &TextureSamplerStateRef);

	if (FAILED(hr))
		return false;

	return true;
}
