#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<int> a;


int AddRecur(int num)
{
	if (num == 1)
		return 1;

	return num + AddRecur(num - 1);
}


int main()
{

	cout << AddRecur(10) << endl;


	return 0;
	
}
