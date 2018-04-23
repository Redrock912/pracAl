#include <iostream>
using namespace std;

int main()
{
	int Array[100];

	for (int i = 0; i < 100; i++)
	{
		Array[i] = i;
	}

	cout << *(Array + 1) << endl;
	return 0;

}
