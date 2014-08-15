#include <iostream>
#include <stack>
#include <ctime>
#include <cstdlib>

#define CHAMBERS 20

using namespace std;

const int grid_size = 2 * CHAMBERS + 1;
unsigned int Visited = 0;

bool Maze[grid_size][grid_size];

enum Direction
{
	N, S, W, E
};

struct point
{
	int x, y;
};

stack<Direction> Patch;

point Digger;

void Backtrack()
{
	switch (Direction temp = Patch.top())
	{
	case N:
		Digger.y -= 2;
		break;
	case S:
		Digger.y += 2;
		break;
	case W:
		Digger.x -= 2;
		break;
	case E:
		Digger.x += 2;
		break;

	}
	Patch.pop();
}

void SpawnDigger()
{

	srand(time(NULL));

	Digger.x = 2 * (rand() % CHAMBERS) + 1;
	Digger.y = 2 * (rand() % CHAMBERS) + 1;

	Maze[Digger.x][Digger.y] = true;
	Visited++;

}

void ShowPoint(point x)
{
	cout << "(" << x.x << "." << x.y << ")\n";
}

Direction ChooseDirection()
{
	int Dir = rand() % 4;

	return (Direction)Dir;
}

void ShowMaze()
{
	for (int y = 0; y < grid_size; y++)
	{
		for (int x = 0; x < grid_size; x++)
		{
			if (Maze[x][y] == true)
				cout << (char)255;
			else
				cout << (char)219;
		}
		cout << "\n";
	}
}

void Move()
{
	while (Visited<CHAMBERS*CHAMBERS)
	{
		Direction Dir = ChooseDirection();

		if ((Maze[Digger.x - 2][Digger.y] == false && Digger.x != 1) ||
			(Maze[Digger.x + 2][Digger.y] == false && Digger.x != grid_size - 2) ||
			(Maze[Digger.x][Digger.y - 2] == false && Digger.y != 1) ||
			(Maze[Digger.x][Digger.y + 2] == false && Digger.y != grid_size - 2))

		{
			if (Dir == N && Digger.y > 2 && Maze[Digger.x][Digger.y - 2] == false)
			{
				Maze[Digger.x][Digger.y - 1] = true;
				Maze[Digger.x][Digger.y -= 2] = true;
				Patch.push(S);
				Visited++;
			}
			if (Dir == S && Digger.y < grid_size - 3 && Maze[Digger.x][Digger.y + 2] == false)
			{
				Maze[Digger.x][Digger.y + 1] = true;
				Maze[Digger.x][Digger.y += 2] = true;
				Patch.push(N);
				Visited++;
			}
			if (Dir == E && Digger.x < grid_size - 3 && Maze[Digger.x + 2][Digger.y] == false)
			{
				Maze[Digger.x + 1][Digger.y] = true;
				Maze[Digger.x += 2][Digger.y] = true;
				Patch.push(W);
				Visited++;
			}
			if (Dir == W && Digger.x > 2 && Maze[Digger.x - 2][Digger.y] == false)
			{
				Maze[Digger.x - 1][Digger.y] = true;
				Maze[Digger.x -= 2][Digger.y] = true;
				Patch.push(E);
				Visited++;
			}
		}
		else
		{
			Backtrack();
		}
	}
}



int main()
{
	SpawnDigger();
	Move();
	ShowMaze();
	system("pause");
}