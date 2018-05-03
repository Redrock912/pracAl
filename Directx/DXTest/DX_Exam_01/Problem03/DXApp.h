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

	// DX11 멤버 변수
	
	ID3D11Device* DeviceRef; // 렌더링 외의 업무
	ID3D11DeviceContext* DeviceContextRef; // 렌더링 업무
	IDXGISwapChain* SwapChainRef; // 스왑 체인
	ID3D11RenderTargetView* RenderTargetViewRef; // 렌더 타겟

protected:
	bool InitWindow();
	// DX 초기화
	bool InitDirectX();
};