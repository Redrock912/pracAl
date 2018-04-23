#include <iostream>
#include <string>
using namespace std;


int RecurStringLength(string str)
{
	if (str.empty())
		return 0;

	return 1 + RecurStringLength(str.substr(1));
}

int main()
{
	string s;
	cin >> s;
	
	cout << RecurStringLength(s) << endl;
	
	return 0;
	
}
