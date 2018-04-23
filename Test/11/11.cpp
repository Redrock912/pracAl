#include <iostream>
#include <stack>
using namespace std;

class Position {
public:
	int x;
	int y;
};

int Maze[5][5] = {
	{ 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 0 }

};

Position Dir[4];


void PrintMaze(const Position& Current)
{
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			if (Current.x == x && Current.y == y)
			{
				cout << "p ";
			}
			else {
				cout << Maze[x][y] << " ";
			}
		}
		cout << endl;
	}

	cout << "( " << Current.x << " , " << Current.y << ") " << endl;
}


bool CanMove(Position& Current)
{
	Position Next;

	for (int i = 0; i < 4; ++i)
	{
		Next.x = Current.x + Dir[i].x;
		Next.y = Current.y + Dir[i].y;

		if (Next.x <0 || Next.y <0 || Next.x > 5 || Next.y>5)
		{
			//4번 다 물어봐야 함
			continue;
		}

		if (Maze[Next.x][Next.y] == 0)
		{
			Current = Next;
			return true;
		}
	}

	return false;
}


int main()
{
	//up
	Dir[0].x = 0;
	Dir[0].y = -1;

	//right
	Dir[1].x = 1;
	Dir[1].y = 0;

	//down
	Dir[2].x = 0;
	Dir[2].y = 1;

	//left
	Dir[3].x = -1;
	Dir[3].y = 0;

	stack<Position> path;
	Position Start;
	Start.x = 0;
	Start.y = 0;

	while (1)
	{
		
		Maze[Start.x][Start.y] = 2;
		PrintMaze(Start);
		if (!CanMove(Start))
		{
			if (!path.empty())
			{
				Position Temp = path.top();
				path.pop();
				Maze[Start.x][Start.y] = 3;
				Start = Temp;
			}
			else
			{
				cout << "No Exit" << endl;
				break;
			}
		}
		else
		{
			path.push(Start);
		}

		if (Start.x == 4 && Start.y == 4)
		{
			cout << "Exit found" << endl;
			break;
		}

		system("cls");
		
	}



	return 0;

}