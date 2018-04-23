#include <iostream>
using namespace std;

int main()
{
	char* ch;
	char buffer[1024] = { 0 };

	scanf("%s", buffer);
	ch = buffer;
	int l = strlen(buffer);
	ch = (char*)malloc(l * sizeof(char));

	strcpy(ch, buffer);
	cout << ch;
}
