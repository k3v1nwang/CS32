#include <iostream>
#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows),m_cols(nCols)
{
	
	for (int r = 1; r <= nRows; r++)
	{
		for (int c = 1; c <= nCols; c++)
		{
			m_grid[r-1][c-1] = 0;
		}
	}
}

bool History::record(int r, int c)
{
	bool result;
	if (r > m_rows || c > m_cols || r < 1 || c < 1)
		result = false;
	else
		result = true;
	m_grid[r - 1][c - 1] += 1;
	return result;
}

void History::display() const
{
	
	char grid[MAXROWS][MAXCOLS];
	for (int r = 1; r <= m_rows; r++)
	{
		for (int c = 1; c <= m_cols; c++)
		{
			int count = m_grid[r - 1][c - 1];

			if (count == 0)
				grid[r - 1][c - 1] = '.';
			else if (count > 26)
				grid[r - 1][c - 1] = 'Z';
			else
				grid[r - 1][c - 1] = 'A' + count - 1;
		}
	}
	clearScreen();
	
	for (int r = 1; r <= m_rows; r++)
	{
		for (int c = 1; c <= m_cols; c++)
		{
			cout <<grid[r - 1][c - 1];
		}
		cout << endl;
	}
	cout << endl;
	
	
}