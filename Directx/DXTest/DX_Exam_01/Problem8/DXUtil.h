#pragma once
#include <d3d11.h>
#include <d3dx11.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")

// 메모리 해제용 함수들
namespace Memory
{
	template <class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}

	}

	template <class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}

	template <class T> void SafeDeleteArr(T& t)
	{
		if (t)
		{
			delete[] t;
			t = nullptr;
		}
	}
}