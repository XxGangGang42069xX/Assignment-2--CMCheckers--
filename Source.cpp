/*
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
Authors: Nicholas Hung, Mark Cheng, Eli Planas
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
*/
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

//function prototypes
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);


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
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {};
	int xIndicesMove[MAX_PIECES] = {};
	int yIndicesMove[MAX_PIECES] = {};
	int xIndicesJump[MAX_PIECES] = {};
	int yIndicesJump[MAX_PIECES] = {};
	string numRowsInBoardstr;
	int numRowsInBoard;
	int tries;
	int MAXtries;

	numRowsInBoard = 0;
	MAXtries = 3;
	
	for (tries = 0; tries < MAXtries; tries++)
	{
		cout << "Enter the number of squares along each edge of the board\n";
		cin >> numRowsInBoardstr;
		//check the input
		//check if it is an integer
		for (int i = 0; i < numRowsInBoardstr.size(); i++)
		{
			if (!isdigit(numRowsInBoardstr.at(i)))
			{
				cerr << "ERROR: Board size is not an integer.\n8 <= number of squares <= 18\n";
				continue;
			}
		}
		numRowsInBoard = stoi(numRowsInBoardstr);
		//check if it is even
		if (numRowsInBoard % 2 != 0)
		{
			cerr << "ERROR: Board size odd.\n8 <= number of squares <= 18\n";
			continue;
		}
		//check the size
		else if (numRowsInBoard > MIN_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too small.\n8 <= number of squares <= 18\n";
			continue;
		}
		else if (numRowsInBoard < MAX_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too large.\n8 <= number of squares <= 18\n";
			continue;
		}
		else 
		{
			// it is an integer
			break;
		}
	}
	if (tries == 3)
	{
		cerr << "ERROR: Too many errors entering the size of the board.";
		return 0;
	}
	InitializeBoard(myCMCheckersBoard, numRowsInBoard);

}

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{

}













//prototypes the function CountJumps :: fMove it above the int main after
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

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
	
	
