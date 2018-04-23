#pragma once
#include <Windows.h>

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	//Main Message Loop. (â���� ó���ϱ� ����)
	int Run();

	//framework method
	virtual bool Init();
	virtual void Update() = 0; 
	virtual void Render() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	

protected:

	// Win32 ��� ����
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCSTR appTitle;
	DWORD wndStyle; // DWORD == unsinged int

protected:

	// Win32 �޼ҵ�
	//������ �ʱ�ȭ
	bool InitWindow();
};

