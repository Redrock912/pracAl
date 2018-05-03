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
	windowTitle = L"Problem7";
	wndStyle = WS_OVERLAPPEDWINDOW;
	appRef = this;

	// DX ��� ���� �ʱ�ȭ
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

bool DXApp::InitScene()
{
	// ���̴� ������.
	HRESULT hr;
	// ���� ���̴� ������.
	hr = D3DX11CompileFromFile(L"Effects.fx", NULL, NULL, "VS_Main", "vs_5_0", NULL, NULL, NULL, &vertexShaderBuffer, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"������ ����1", L"����", MB_OK);
		return false;
	}

	// ���� ���̴� ������Ʈ ����.
	DeviceRef->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);

	// ���� ���̴� ����.(���ε�).
	DeviceContextRef->VSSetShader(vertexShader, NULL, NULL);

	// �ȼ� ���̴�.
	hr = D3DX11CompileFromFile(L"Effects.fx", NULL, NULL, "PS_Main",
		"ps_5_0", NULL, NULL, NULL, &pixelShaderBuffer, NULL, NULL);

	// �ȼ� ���̴� ������Ʈ ����.
	DeviceRef->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

	// �ȼ� ���̴� ���ε�.
	DeviceContextRef->PSSetShader(pixelShader, NULL, NULL);

	// ���� �����.
	Vertex vertices[] =
	{
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f),
		Vertex(0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.1f, 0.0f, 1.0f, 1.0f),
	};

	DWORD indices[] =
	{
		0,1,2,
		0,2,3,
	};

	// sizeof(vertices) / sizeof(vertices[0]);
	// ���ؽ� ���� ������(Descriptor).
	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	// ���� ���ҽ� ����.
	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = vertices;

	// ���� ���� ����.
	DeviceRef->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);

	// �ε��� ���� ������(Descriptor).
	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.ByteWidth = sizeof(DWORD) * ARRAYSIZE(indices);
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	// ���� ���ҽ� ����.
	D3D11_SUBRESOURCE_DATA ibData;
	ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibData.pSysMem = indices;

	// �ε��� ���� ����.
	DeviceRef->CreateBuffer(&ibDesc, &ibData, &indexBuffer);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// ���� ���� ���ε�.
	DeviceContextRef->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	DeviceContextRef->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// �Է� ���̾ƿ�.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// �Է� ���̾ƿ� ����.
	DeviceRef->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &vertexInputLayout);

	// �Է� ���̾ƿ� ���ε�.
	DeviceContextRef->IASetInputLayout(vertexInputLayout);

	// �⺻ �������� ���� (TRIANGLELIST�� ����).
	DeviceContextRef->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ����Ʈ ���� ����.
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = userWidth;
	viewport.Height = userHeight;

	// ����Ʈ ����.
	DeviceContextRef->RSSetViewports(1, &viewport);

	// World x View x Projection;
	// ���� ���. (��ġ/ȸ��/������).
	world = XMMatrixIdentity();

	// ī�޶� ��ġ.
	cameraPos = XMVectorSet(1.0f, 2.0f, -2.0f, 0.0f);

	// ī�޶� �ٶ󺸴� ��ġ.
	cameraTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	// ī�޶� �� ����.
	cameraUp = XMVectorSet(5.0f, 2.0f, 0.0f, 0.0f);

	// �� ���.
	view = XMMatrixLookAtLH(cameraPos, cameraTarget, cameraUp);

	// �þ߰�.
	float fovY = 75.0f * 3.14 / 180.0f;

	// ���� ���.
	projection = XMMatrixPerspectiveFovLH(fovY, (float)userWidth / userHeight,
		1.0f, 1000.0f);

	// ��� ���� ������ ���� �� ���������� ���ε�.
	// ��ġ����� ���� ������ ä���.
	// DX�� ��켱 / HLSL�� ���켱.
	CBPerObject data;
	data.world = XMMatrixTranspose(world);
	data.view = XMMatrixTranspose(view);
	data.projection = XMMatrixTranspose(projection);

	// ���� ��ũ����.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = sizeof(CBPerObject);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	// ���� ���ҽ� ����.
	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &data;

	// ��� ���� ����.
	hr = DeviceRef->CreateBuffer(&cbDesc, &cbData, &cbBuffer);

	// ���������ο� ���ε�.
	DeviceContextRef->VSSetConstantBuffers(0, 1, &cbBuffer);


	return true;
}
