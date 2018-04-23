#include <iostream>

using namespace std;

class Node 
{
public:
	Node* Left;
	Node* Right;
	int Data;

	void SetData(int Value);
	void MakeLeftChild(int Value=0);
	void MakeRightChild(int Value=0);

};

class Tree
{
public:
	Node* Root;
	void PreSearch(Node* Root);
};

void Node::SetData(int Value)
{
	Data = Value;
}

void Node::MakeLeftChild(int i)
{
	Left = new Node();
	Left->Data = i;
}

void Node::MakeRightChild(int i)
{
	Right = new Node();
	Right->Data = i;
}

void Tree::PreSearch(Node* Root)
{
	if (Root != NULL)
	{
		cout << Root->Data << endl;
		PreSearch(Root->Left);
		PreSearch(Root->Right);
	}
}



int main()
{
	Tree T;
	T.Root = new Node();
	T.Root->SetData(1);
	T.Root->MakeLeftChild(2);
	T.Root->MakeRightChild(3);
	T.Root->Left->MakeLeftChild(4);
	T.Root->Left->MakeRightChild(5);

	T.PreSearch(T.Root);

	return 0;
}
