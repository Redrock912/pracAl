#ifndef __AQUEUE_H__
#include <iostream>

using namespace std;

template<typename T>
class AQueue
{
public:
	void Init(int size = 3); //�迭�� �ʱ�ȭ
	void Enqueue(T Value);
	void Dequeue(T& Value); // ���۷����� �ޱ�
	bool Empty() { return Size == 0 };
	int Length() { return Size };
	void Peek(T& Value);

protected:
	T* Data;
	int Head;
	int Tail;
	int Size;
	int Capacity;
};

template<typename T>
void AQueue<T>::Init(int size)
{
	Data = new T[size];
	Capacity = size;
	Size = 0;
	Head = 0;
	Tail = 0;
}

template<typename T>
void AQueue<T>::Enqueue(T Value)
{
	if (Size < Capacity)
	{
		Data[Tail++] = Value; // ���� �ְ� tail �� �ű�. �� �ִ°��� ���x
		Size++;
		Tail = Tail % Capacity;
	}
	else
	{
		cout << "overflow" << endl;
	}
}

template<typename T>
void AQueue<T>::Dequeue(T & Value)
{
	if (Size > 0)
	{
		Value = Data[Head++];
		Head = Head % Capacity;
		Size--;
	}
	else
	{
		cout << "It's Empty" << endl;
	}

}

template<typename T>
void AQueue<T>::Peek(T & Value)
{
	Value = Data[Head];
}


#endif // !__AQUEUE_H__

