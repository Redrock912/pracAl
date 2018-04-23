#pragma once

// 메모리 해제용 도움 함수
namespace Memory
{

	// DX 인터페이스 해제용
	template <class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}

	// 동적 할당한 인스턴스 해제용
	template <class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}

	// 배열 해제용
	template <class T> void SafeDeleteArr(T& t)
	{
		if (t)
		{
			delete[] t;
			t = nullptr;
		}
	}

	
}