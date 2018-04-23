#include <iostream>
#include <queue>
#include <conio.h>
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
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 5; ++y)
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


bool CanMove(const Position& Current, Position& NewPosition, int dir) //const 은 보는것만 되고, 없는 것은 출력도 가능
{
	Position Next;
	Next.x = Current.x + Dir[dir].x;
	Next.y = Current.y + Dir[dir].y;

	if (Next.x<0 || Next.y < 0 || Next.x > 4 || Next.y > 4)
	{
		return false;
	}

	if (Maze[Next.x][Next.y] == 0)
	{
		NewPosition = Next;
		return true;
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

	queue<Position> path;
	Position Start;
	Start.x = 0;
	Start.y = 0;
	path.push(Start);
	Maze[0][0] = 10;
	
	while (!path.empty())
	{
		Start = path.front();
		path.pop();
		
		for (int i = 0; i < 4; i++) // up,down,left,right search
		{
			Position NewPosition;
			if (CanMove(Start, NewPosition, i))
			{
				Maze[NewPosition.x][NewPosition.y] = Maze[Start.x][Start.y] + 1; // 이동할때마다 비용을 올려준다.
				if (NewPosition.x == 4&& NewPosition.y == 4)
				{
					cout << "Done" << endl;
					break;
				}


				path.push(NewPosition);
			}


		}
		PrintMaze(Start);
		getch();
		system("cls");
	}



	return 0;

}