//#include "AQueue.h"
#include <iostream>
#include <queue>
#include <conio.h>
#include <stack>
using namespace std;

class Position
{
public:
	int x;
	int y;
};



Position Dir[4];

#define MAX 20
#define PATH 0
#define WALL 1
#define VISITED 2
#define BACKTRACE 3

int Maze[MAX][MAX] = {
	{ 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
	{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 },
	{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0 },
	{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
	{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
	{ 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
	{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0 }
};

void InitDir()
{
	//Up
	Dir[0].x = 0;
	Dir[0].y = -1;

	//Right
	Dir[1].x = 1;
	Dir[1].y = 0;

	//Down
	Dir[2].x = 0;
	Dir[2].y = 1;

	//Left
	Dir[3].x = -1;
	Dir[3].y = 0;
}

bool CanMove(const Position& Current,Position& NewPosition, int dir) //const 은 보는것만 되고, 없는 것은 출력도 가능
{
	Position Next;
	Next.x = Current.x + Dir[dir].x;
	Next.y = Current.y + Dir[dir].y;

	if (Next.x<0 || Next.y < 0 || Next.x > MAX-1 || Next.y > MAX-1) 
	{
		return false;
	}

	if (Maze[Next.y][Next.x] == PATH)
	{
		NewPosition = Next;
		return true;
	}
	
	return false;
}

void PrintMaze(const Position& Current)
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (Current.x == x && Current.y == y)
			{
				cout << "P" << "  ";
			}
			else
			{
				cout << Maze[y][x] << "  ";
			}
		}
		cout << endl;
	}

	cout << "(" << Current.y << "," << Current.x << ")" << endl;
}

int main()
{
	//AQueue<int> Q;
	//Q.Init(10);
	//int temp;
	//Q.Enqueue(1);
	//Q.Dequeue(temp);
	//Q.Enqueue(2);
	//Q.Dequeue(temp);
	//Q.Enqueue(3);
	//Q.Enqueue(4);
	//Q.Enqueue(5);
	//Q.Dequeue(temp);
	//Q.Dequeue(temp);
	//Q.Dequeue(temp);
	//Q.Enqueue(6);
	//Q.Enqueue(7);
	//Q.Enqueue(8);
	//Q.Enqueue(9);
	//Q.Enqueue(10);
	//Q.Enqueue(11);
	//Q.Enqueue(12);
	//Q.Enqueue(13);
	//Q.Enqueue(14);

	queue<Position> Q;
	//Q.Init(1000); // 지금 aqueue 는 예외처리가안되있으므로 그냥 크게 잡는다.
	InitDir();
	// 처음 위치
	Position Current;
	Current.x = 0;
	Current.y = 0;

	Q.push(Current);
	Maze[0][0] = 10; // 갔던 위치 마킹
	bool found = false;



	while (!Q.empty())
	{
		Current = Q.front();
		Q.pop();
		int PrevLevel = Maze[Current.y][Current.x];
		for (int i = 0; i < 4; i++) // up,down,left,right search
		{
			Position NewPosition;
			if (CanMove(Current,NewPosition, i))
			{
				Maze[NewPosition.y][NewPosition.x] = Maze[Current.y][Current.x] +1; // 이동할때마다 비용을 올려준다.
				if (NewPosition.x == MAX - 1 && NewPosition.y == MAX - 1)
				{
					cout << "Done" << endl;
					break;
				}

				
				Q.push(NewPosition);
			}

			
		}
		PrintMaze(Current);
		getch();
		system("cls");
	}


	return 0;
}