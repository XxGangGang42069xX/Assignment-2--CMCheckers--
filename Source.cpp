/*
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
Authors: Nicholas Hung, Mark Cheng, Eli Planas
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
*/
#include <iostream>

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
	int numRowsInBoard;
	int [y][x];
	xIndicesJump[MAX_PIECES];
	yIndicesJump[MAX_PIECES];
	cout << "Enter the number of squares along each edge of the board";
	cin >> numRowsInBoard; //must be 8-18, even, and an integer, 3 chances
	
	if (!numRowsInBoard)
	{
		cerr << "ERROR: Board size is not an integer.";
		return 1;
	}
	else if (numRowsInBoard < 8)
	{
		cerr << "ERROR: Board size too small.";
		return 1;
	}
	else if (numRowsInBoard > 18)
	{
		cerr << "ERROR: Board size too large.";
		return 1;
	}
	else if (%numRowsInBoard == 1)
	{
		cerr << "ERROR: Board size odd.";
		return 1;
	}


}












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
	
	
