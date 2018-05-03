#pragma once
#include <Windows.h>
#include "DXUtil.h"

class DXApp
{
public:
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

protected:
	bool InitWindow();
	// DX �ʱ�ȭ
	bool InitDirectX();
};