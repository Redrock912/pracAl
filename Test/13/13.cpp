#include <iostream>
#include <stack>

using namespace std;

int main()
{
	stack<int> bin;
	int i;
	cin >> i;

	while (i / 2 != 0)
	{
		bin.push(i % 2);
		i = i / 2;

	}
	bin.push(i);

	while (!bin.empty())
	{
		cout << bin.top();
		bin.pop();
	}
	cout << endl;

	return 0;
}