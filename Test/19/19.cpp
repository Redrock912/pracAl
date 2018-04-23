#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX 10

#define WAY 0
#define WALL 1
#define BLOCK 2
#define PATH 3



int Maze[MAX][MAX] =
{
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
	{ 1, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
	{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 1, 0, 0 },
	{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }
};

int FindWall(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAX || y >= MAX)
	{
		return 0;
	}
	else if (Maze[y][x] != WALL)
	{
		return 0;
	}
	else 
	{
		Maze[y][x] = BLOCK;
		return 1+FindWall(x, y - 1) +
			FindWall(x + 1, y) +
			FindWall(x, y + 1) +
			FindWall(x - 1, y) +
			FindWall(x+1,y+1) + 
			FindWall(x+1,y-1) +
			FindWall(x-1,y-1) +
			FindWall(x-1,y+1);
	}
}

void PrintMaze()
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			cout << Maze[y][x] << " ";
		}
		cout << endl;
	}
}


int main()
{
	
	cout << FindWall(0,1) << endl;
	
	PrintMaze();
	
	return 0;
}
