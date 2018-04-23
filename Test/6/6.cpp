#include <iostream>
#include <list>
#include <conio.h>
using namespace std;

class Text
{
public:
	Text() {}
	char data[80];
};

int main()
{
	list<Text> file;

	FILE* fp = fopen("test.txt", "r");
	char buffer[81] = { 0 };
	char buffer2[1024] = { 0 };

	if (fp != nullptr)
	{
		while (!feof(fp))
		{
			memset(buffer, 0, 81);
			fgets(buffer, 80, fp);
			Text Temp;
			memcpy(Temp.data, buffer, 80);
			file.push_back(Temp);
		}

		fclose(fp);
	}

	
	char InputKey='0';
	int line = 0;

	while (InputKey != 'q')
	{
		
		list<Text> temp = file;
		for (int i = 0; i < line; i++)
		{
			temp.pop_front();
		}


		for (int i = line; i < line+5; ++i)
		{
			cout << temp.front().data << endl;
			temp.pop_front();
		}

		InputKey = getch();

		if (InputKey == 'w')
		{
			line--;
		}
		else if (InputKey == 's')
		{
			line++;
		}
		system("cls");
	}


	return 0;
}
