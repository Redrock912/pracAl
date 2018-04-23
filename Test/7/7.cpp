#include <iostream>
#include <list>
#include <conio.h>
using namespace std;


class MyStack
{
protected:
	list<int> data;
public:
	void Push(int Value);
	void Pop();
	int Peek();
	int Length() { return data.size(); }
	
};

void MyStack::Push( int Value)
{
	data.push_back(Value);
}

void MyStack::Pop()
{
	data.pop_back();
}

int MyStack::Peek()
{
	return data.back();
}


int main()
{
	MyStack Stack;
	

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
