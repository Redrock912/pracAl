#pragma once
#include <Windows.h>
#include "DXUtil.h"
#include <xnamath.h>

class DXApp
{
public:

	// ���� ����ü
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;

		Vertex() {}
		Vertex(float x, float y, float z,float r,float g, float b, float a) : position(x, y, z), color(r,g,b,a) {}
		Vertex(XMFLOAT3 pos, XMFLOAT4 color) : position(pos), color(color) {}
	};

	// ��� ���ۿ� ����ü ����
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

	// DX11 ��� ����
	
	ID3D11Device* DeviceRef; // ������ ���� ����
	ID3D11DeviceContext* DeviceContextRef; // ������ ����
	IDXGISwapChain* SwapChainRef; // ���� ü��
	ID3D11RenderTargetView* RenderTargetViewRef; // ���� Ÿ��

	ID3D11Buffer* vertexBuffer; // ���ؽ� 
	ID3D11VertexShader* vertexShader; // ���̴� 
	ID3D11PixelShader* pixelShader; // �ȼ� ���̴�
	ID3DBlob* vertexShaderBuffer; // ���ؽ� ���̴� ����
	ID3DBlob* pixelShaderBuffer; // �ȼ� ���̴� ����
	ID3D11InputLayout* vertexInputLayout; //���� �Է¿� ���̾ƿ�

	ID3D11Buffer* indexBuffer; // �ε��� ����

	// ���� ��ȯ ���.
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;

	// ����� ���� �� �ʿ��� ��.
	XMVECTOR cameraPos;
	XMVECTOR cameraTarget;
	XMVECTOR cameraUp;

	// ��� ����.
	ID3D11Buffer* cbBuffer;

protected:
	bool InitWindow();
	// DX �ʱ�ȭ
	bool InitDirectX();
	// �� �ʱ�ȭ
	bool InitScene();
};