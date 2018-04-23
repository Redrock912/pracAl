#include <iostream>
using namespace std;

class Node
{
public:
	int Value;
	Node* Next = NULL;
	Node* Prev = NULL;
};

class DList
{
public:
	Node* Head;
	Node* Tail;
	Node* CreateNode(int Value);
	void AddNode(Node** Head, int Value);

};
void DList::AddNode(Node** Head, int i) {
	Node* NewNode = new Node;
	NewNode->Value = i;
	NewNode->Next = NULL;
	NewNode->Prev = NULL;
	if (*Head == NULL) {

		*Head = NewNode;
	}
	else {
		Node* Last = *Head;
		while (Last->Next != NULL)
		{
			Last = Last->Next;
		}
		Last->Next = NewNode;
		NewNode->Prev = Last;
		Tail = NewNode;
	}


}

int main()
{
	DList dlist;
	Node* Head = NULL;

	for (int i = 1; i <= 10; i++)
	{
		dlist.AddNode(&Head, i);
	}

	Node* Current = dlist.Tail;
	while (Current != NULL)
	{
		cout << Current->Value;
		Current = Current->Prev;
	}

	return 0;
}
