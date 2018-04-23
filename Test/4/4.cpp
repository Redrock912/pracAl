#include <iostream>
using namespace std;

class Node
{
public:
	int Value;
	Node* Next = NULL;
};

void AddNode(Node** Head, int i) {
	Node* NewNode = new Node;
	NewNode->Value = i;
	NewNode->Next = NULL;
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
	}


}

int main()
{
	Node* First = NULL;

	for (int i = 1; i <= 10; i++)
	{
		AddNode(&First, i);
	}

	Node* Current = First;
	while (Current != NULL)
	{
		cout << Current->Value;
		Current = Current->Next;
	}

	return 0;
}
