#pragma once
#include <Windows.h>
#include "DXUtil.h"
#include <xnamath.h>

class DXApp
{
public:

	// 정점 구조체
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;

		Vertex() {}
		Vertex(float x, float y, float z,float r,float g, float b, float a) : position(x, y, z), color(r,g,b,a) {}
		Vertex(XMFLOAT3 pos, XMFLOAT4 color) : position(pos), color(color) {}
	};

	// 상수 버퍼용 구조체 정의
	struct CBPerObject
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	int Run();

	virtual bool Init();
	virtual void Update()=0;
	virtual void Render()=0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HWND hwnd;
	HINSTANCE hinstance;
	UINT userWidth;
	UINT userHeight;
	LPCWSTR windowTitle;
	DWORD wndStyle;

	// DX11 멤버 변수
	
	ID3D11Device* DeviceRef; // 렌더링 외의 업무
	ID3D11DeviceContext* DeviceContextRef; // 렌더링 업무
	IDXGISwapChain* SwapChainRef; // 스왑 체인
	ID3D11RenderTargetView* RenderTargetViewRef; // 렌더 타겟

	ID3D11Buffer* vertexBuffer; // 버텍스 
	ID3D11VertexShader* vertexShader; // 쉐이더 
	ID3D11PixelShader* pixelShader; // 픽셀 쉐이더
	ID3DBlob* vertexShaderBuffer; // 버텍스 쉐이더 버퍼
	ID3DBlob* pixelShaderBuffer; // 픽셀 쉐이더 버퍼
	ID3D11InputLayout* vertexInputLayout; //정점 입력용 레이아웃

	ID3D11Buffer* indexBuffer; // 인덱스 버퍼

	// 공간 변환 행렬.
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;

	// 뷰행렬 만들 때 필요한 값.
	XMVECTOR cameraPos;
	XMVECTOR cameraTarget;
	XMVECTOR cameraUp;

	// 상수 버퍼.
	ID3D11Buffer* cbBuffer;

protected:
	bool InitWindow();
	// DX 초기화
	bool InitDirectX();
	// 씬 초기화
	bool InitScene();
};