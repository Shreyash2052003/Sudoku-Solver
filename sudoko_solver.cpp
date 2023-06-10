#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for (int i = a; i < b; i = i + 1)
#define ff first
#define ss second
#define setsBits(x) builtin_popcount()

void helper(int r, int c, vector<vector<char>> &a, map<pair<int, int>, map<int, int>> &mp, vector<map<int, int>> &row, vector<map<int, int>> &col)
{
	if (r == 9)
	{
		for (auto it : a)
		{
			for (auto i : it)
			{
				cout << i << " ";
			}
			cout << "\n";
		}
		cout << "\n";
		return;
	}
	if (c == 9)
	{
		helper(r + 1, 0, a, mp, row, col);
		return;
	}
	if (a[r][c] != '.')
	{
		helper(r, c + 1, a, mp, row, col);
		return;
	}
	for (int i = 1; i <= 9; i = i + 1)
	{
		int rw = r / 3, cl = c / 3;
		if (!mp[{rw, cl}][i] and !row[r][i] and !col[c][i])
		{
			mp[{rw, cl}][i] = 1;
			row[r][i] = 1;
			col[c][i] = 1;
			a[r][c] = i + '0';
			helper(r, c + 1, a, mp, row, col);
			mp[{rw, cl}][i] = 0;
			row[r][i] = 0;
			col[c][i] = 0;
			a[r][c] = '.';
		}
	}
}
void solvesudoko(vector<vector<char>> &a)
{   int checksudoko=0;
	map<pair<int, int>, map<int, int>> mp;
	vector<map<int, int>> row(9);
	vector<map<int, int>> col(9);
	for (int i = 0; i < 9; i = i + 1)
	{
		for (int j = 0; j < 9; j = j + 1)
		{
			if (a[i][j] != '.')
			{
				if(mp[{i / 3, j / 3}][a[i][j] - '0'] ==0)
				{mp[{i / 3, j / 3}][a[i][j] - '0'] = 1+mp[{i / 3, j / 3}][a[i][j] - '0'];
				}
				else
				{
					checksudoko=1;
				}if(row[i][a[i][j] - '0']==0)
				{row[i][a[i][j] - '0'] = 1+row[i][a[i][j] - '0'] ;
				}
				else
				{
					checksudoko=1;
				}
				if(col[j][a[i][j] - '0'] ==0)
				{col[j][a[i][j] - '0'] = 1+col[j][a[i][j] - '0'] ;}
				else
				{
					checksudoko=1;
				}
			}
		}
	}
if(checksudoko==0)
	{helper(0, 0, a, mp, row, col);}
	else
	{
		cout<<"no"<<endl;
	}
}
int main()
{
	vector<vector<char>> sudoko = {
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
	solvesudoko(sudoko);
}

/*
// A Backtracking program in
// C++ to solve Sudoku problem
#include <bits/stdc++.h>
using namespace std;

// UNASSIGNED is used for empty
// cells in sudoku grid
#define UNASSIGNED 0

// N is used for the size of Sudoku grid.
// Size will be NxN
#define N 9

// This function finds an entry in grid
// that is still unassigned
bool FindUnassignedLocation(int grid[N][N],
							int& row, int& col);

// Checks whether it will be legal
// to assign num to the given row, col
bool isSafe(int grid[N][N], int row,
			int col, int num);

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
/*bool SolveSudoku(int grid[N][N])
{
	int row, col;

	// If there is no unassigned location,
	// we are done
	if (!FindUnassignedLocation(grid, row, col))
		// success!
		return true;

	// Consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{

		// Check if looks promising
		if (isSafe(grid, row, col, num))
		{

			// Make tentative assignment
			grid[row][col] = num;

			// Return, if success
			if (SolveSudoku(grid))
				return true;

			// Failure, unmake & try again
			grid[row][col] = UNASSIGNED;
		}
	}

	// This triggers backtracking
	return false;
}

/* Searches the grid to find an entry that is
still unassigned. If found, the reference
parameters row, col will be set the location
that is unassigned, and true is returned.
If no unassigned entries remain, false is returned. */
/*bool FindUnassignedLocation(int grid[N][N],
							int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number.
bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
/*/*bool UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number.
bool UsedInBox(int grid[N][N], int boxStartRow,
			int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow]
					[col + boxStartCol] ==
									num)
				return true;
	return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location.
bool isSafe(int grid[N][N], int row,
			int col, int num)
{
	/* Check if 'num' is not already placed in
	current row, current column
	and current 3x3 box
	return !UsedInRow(grid, row, num)
		&& !UsedInCol(grid, col, num)
		&& !UsedInBox(grid, row - row % 3,
						col - col % 3, num)
		&& grid[row][col] == UNASSIGNED;
}

/* A utility function to print grid
void printGrid(int grid[N][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
			cout << grid[row][col] << " ";
		cout << endl;
	}
}

// Driver Code
int main()
{
	// 0 means unassigned cells
	int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
					{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
					{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
					{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
					{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
					{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
					{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
	if (SolveSudoku(grid) == true)
		printGrid(grid);
	else
		cout << "No solution exists";

	return 0;
}

// This is code is contributed by rathbhupendra

*/