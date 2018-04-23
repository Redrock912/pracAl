#pragma once
#include <Windows.h>

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	//Main Message Loop. (창에서 처리하기 위한)
	int Run();

	//framework method
	virtual bool Init();
	virtual void Update() = 0; 
	virtual void Render() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	

protected:

	// Win32 멤버 변수
	HWND hwnd;
	HINSTANCE hinstance;
	UINT clientWidth;
	UINT clientHeight;
	LPCSTR appTitle;
	DWORD wndStyle; // DWORD == unsinged int

protected:

	// Win32 메소드
	//윈도우 초기화
	bool InitWindow();
};

