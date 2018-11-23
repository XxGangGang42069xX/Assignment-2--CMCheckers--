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
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

//define the function CountJumps :: Kill me
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	//declare all local variables
	int jumps = 0;
	int i = 0;
	int xIndex = 0;
	int yIndex = 0;

	//initialize all elements of yLocArray and xLocaray to -1
	for (i = 0; i < MAX_PIECES ; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}
	if (player == REDPLAYER) //red players
	{
		for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
		{
			for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
			{
				if ((xLocArray[xIndex], yLocArray[yIndex]) == (REDKING || REDMULE || REDSOLDIER))
				{
					if (IsJump(CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], numRowsInBoard, player, xIndex, yIndex) == true)
					{
						xLocArray[jumps] = xIndex;
						yLocArray[jumps] = yIndex;
						jumps++;
					}
				}
				else if ((xLocArray[xIndex], yLocArray[yIndex]) != (REDKING || REDMULE || REDSOLDIER))
				{
					continue;
				}
			}
		}
		return jumps;
	}
	if (player == WHITEPLAYER) //white players
	{
		for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
		{
			for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
			{
				if ((xLocArray[xIndex], yLocArray[yIndex]) == (WHITEKING || WHITEMULE || WHITESOLDIER))
				{
					if (IsJump(CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], numRowsInBoard, player, xIndex, yIndex) == true)
					{
						xLocArray[jumps] = xIndex;
						yLocArray[jumps] = yIndex;
						jumps++;
					}
				}
			}
		}
		return jumps;
	}

}


//prototype function CountMove1Squares
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

//define the function CountMove1Squares
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int i = 0;
	int xindex = 0;
	int yindex = 0;
	int count = 0;


	for (i = 0; i < MAX_PIECES; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}
	
	
	if (player == REDPLAYER)		//red player
	{
		for (xindex = 0; xindex < numRowsInBoard; xindex++)
		{
			for (yindex = 0; yindex < numRowsInBoard; yindex++)
			{
				if ((xLocArray[xindex], yLocArray[yindex]) == (REDKING || REDMULE || REDSOLDIER))
				{
					if (IsMove1Square(CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], numRowsInBoard, player, xindex, yindex) == true)
					{
						xLocArray[count] = xindex;
						yLocArray[count] = yindex;
						count++;
					}
				}
			}
		}
		return count;
	}
	if (player == WHITEPLAYER)		//white player
	{
		for (xindex = 0; xindex < numRowsInBoard; xindex++)
		{
			for (yindex = 0; yindex < numRowsInBoard; yindex++)
			{
				if ((xLocArray[xindex], yLocArray[yindex]) == (REDKING || REDMULE || REDSOLDIER))
				{
					if (IsMove1Square(CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], numRowsInBoard, player, xindex, yindex) == true)
					{
						xLocArray[count] = xindex;
						yLocArray[count] = yindex;
						count++;
					}
				}
			}
		}
		return count;
	}

}

//prototype the function IsMove1Square
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc);

//define the function IsMove1Square
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == REDPLAYER)//red player
	{
		if (CMCheckersBoard[xLoc][yLoc] == (REDMULE || REDSOLDIER || REDKING))
		{
			//check if front right/left are available to move to
			if (CMCheckersBoard[xLoc + 1][yLoc + 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
			{
				if (CMCheckersBoard[xLoc - 1][yLoc + 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
				{
					//check if back right/left are available to move
					if (CMCheckersBoard[xLoc][yLoc] == (REDKING))
					{
						if (CMCheckersBoard[xLoc - 1][yLoc - 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
						{
							if (CMCheckersBoard[xLoc + 1][yLoc -1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
							{
								return false;
							}
						}
						
					}
					return false;
				}
			}
			return true;
		}
	}

	if (player == WHITEPLAYER)//white player
	{
		if (CMCheckersBoard[xLoc][yLoc] == (WHITEMULE || WHITESOLDIER || WHITEKING))
		{
			//check if front right/left are available to move to
			if (CMCheckersBoard[xLoc + 1][yLoc - 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
			{
				if (CMCheckersBoard[xLoc - 1][yLoc - 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
				{
					//check if back right/left are available to move
					if (CMCheckersBoard[xLoc][yLoc] == (REDKING))
					{
						if (CMCheckersBoard[xLoc - 1][yLoc + 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
						{
							if (CMCheckersBoard[xLoc + 1][yLoc + 1] == (WHITESOLDIER || WHITEMULE || WHITEKING || REDSOLDIER || REDMULE || REDKING))
							{
								return false;
							}
						}

					}
					return false;
				}
			}
			return true;
		}
	}
	return 0;
}
