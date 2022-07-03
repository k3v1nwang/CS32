#include<string>
#include <iostream>
#include<stack>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
	Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
	int r() const { return m_row; }
	int c() const { return m_col; }
private:
	int m_row;
	int m_col;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;

	Coord start(sr, sc);
	coordStack.push(start);
	maze[sr][sc] = '@';

	while (!coordStack.empty())
	{
		Coord curr = coordStack.top();
		int x = curr.r();
		int y = curr.c();
		cout << x << ',' << y << endl;
		coordStack.pop();

		if (x == er && y == ec)
			return true;

		if (maze[x - 1][y] == '.' && maze[x - 1][y] != 'X')              //NORTH
		{
			Coord dir(x - 1, y);
			coordStack.push(dir);
			maze[x - 1][y] = '@';
		}

		if (maze[x][y + 1] == '.' && maze[x][y + 1] != 'X')			//EAST
		{
			Coord dir(x, y + 1);
			coordStack.push(dir);
			maze[x][y + 1] = '@';
		}

		if (maze[x + 1][y] == '.' && maze[x + 1][y] != 'X')			//SOUTH
		{
			Coord dir(x + 1, y);
			coordStack.push(dir);
			maze[x + 1][y] = '@';
		}

		if (maze[x][y - 1] == '.' && maze[x][y - 1] != 'X')			//WEST
		{
			Coord dir(x, y - 1);
			coordStack.push(dir);
			maze[x][y -1] = '@';
		}

	}
	return false;

}

int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','.','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
