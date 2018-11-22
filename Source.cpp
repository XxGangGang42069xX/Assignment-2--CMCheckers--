/*
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
Authors: Nicholas Hung, Mark Cheng, Eli Planas
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
*/
#include <iostream>
#include <cmath>

using namespace std;

//Global variables
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

int main()
{
	int [y][x];
	
	int numRowsInBoard;
	xIndicesJump[MAX_PIECES];
	yIndicesJump[MAX_PIECES];
	
	while (m < 3)
	{
		cout << "Enter the number of squares along each edge of the board";
		cin >> numRowsInBoard; //must be 8-18, even, and an integer, 3 chances
	
		if (!numRowsInBoard)//if not an integer
		{
			cerr << "ERROR: Board size is not an integer.\n8 <= number of squares <= 18\n";
			continue;
		}
		else if (numRowsInBoard < 8)// if too small
		{
			cerr << "ERROR: Board size too small.\n8 <= number of squares <= 18\n";
			continue;
		}
		else if (numRowsInBoard > 18)//if too big
		{
			cerr << "ERROR: Board size too large.\n8 <= number of squares <= 18\n";
			continue;
		}
		else if (numRowsInBoard%2 == 1)// if not even
		{
			cerr << "ERROR: Board size odd.\n8 <= number of squares <= 18\n";
			continue;
		}
		m++;
		if (m==3)// if too many tries
		{
			cerr << "ERROR: Too many errors entering the size of the board.";
			return 1;
		}
	}
	
	//step 8
	int CMCheckersBoard












//prototypes the function CountJumps :: fMove it above the int main after
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

//define the function CountJumps :: Kill me
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	//initialize all elements of yLocArray and xLocaray to -1
	int xLocArray[];
	int yLocArray[];
	int index;
	
	for (index = 0; index < ; index++)
	{
		xLocArray[] = -1;
	}
	for (index = 0; index < ; index++)
	{
		yLocArray[] = -1;
	}
	
}
	
	
