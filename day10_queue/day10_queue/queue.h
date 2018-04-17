#ifndef __QUEUE_H__

#include <list>

using namespace std;

template<typename T>
class MyQueue
{
public:
	void Enqueue(T Value);
	void Dequeue(T& Value); // 레퍼런스로 받기
	bool Empty();
	int Length();
	void Peek(T& Value);

protected:
	list<T> Data;
};

template<typename T>
void MyQueue<T>::Enqueue(T Value)
{
	Data.push_back(Value);
}

template<typename T>
void MyQueue<T>::Dequeue(T & Value)
{
	Value = Data.front();
	Data.pop_front();
}

template<typename T>
bool MyQueue<T>::Empty()
{
	return Data.empty();
}

template<typename T>
int MyQueue<T>::Length()
{
	return Data.size();
}

template<typename T>
void MyQueue<T>::Peek(T & Value)
{
	Value = Data.front();
}


#endif // !__QUEUE_H__

