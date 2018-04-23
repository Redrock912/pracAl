#include <iostream>
#include <list>
#include <conio.h>
using namespace std;


class MyQueue
{
protected:
	list<int> data;
public:
	void Push(int Value);
	void Pop();
	int Peek();
	int Length() { return data.size(); }

};

void MyQueue::Push(int Value)
{
	data.push_back(Value);
}

void MyQueue::Pop()
{
	data.pop_front();
}

int MyQueue::Peek()
{
	return data.front();
}


int main()
{
	MyQueue Stack;


	for (int i = 1; i <= 10; i++)
	{
		Stack.Push(i);
	}

	for (int i = 0; i < 10; i++)
	{
		cout << Stack.Peek() << endl;
		Stack.Pop();
	}


	return 0;
}
