#pragma once

// �޸� ������ ���� �Լ�
namespace Memory
{

	// DX �������̽� ������
	template <class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}

	// ���� �Ҵ��� �ν��Ͻ� ������
	template <class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}

	// �迭 ������
	template <class T> void SafeDeleteArr(T& t)
	{
		if (t)
		{
			delete[] t;
			t = nullptr;
		}
	}

	
}