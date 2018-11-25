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

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

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
	DisplayBoard(myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], numRowsInBoard);

	player = WHITEPLAYER;
	if (CountJumps == 0)// if the player has no more jumps
	{
		if (CountMove1Squares == 0)// if the player has no more moves
		{
			//the player has no more moves = he loses
			cout << "White is unable to move.\nGAME OVER, Red has won.\nEnter any character to close the game.";
			return 0;
		}
	}
	else
	{
		cout << "White takes a turn.\n";
	}
	
	while (!squarechoice)
	{
		cout << "Enter the square number of the checker you want to move\n";
		cin >> squarechoice;
		if (!squarechoice)//not an integer
		{
			cerr << "ERROR: You did not enter an integer\nTry again\n";
			continue;
		}
		if (squarechoice is not on the board)//chosen square is not on the board
		{
			cerr << "ERROR: That square is not on the board.\nTry again\n";
			continue;
		}
		if (squarechoice is not your checker)//chose and opponent's checker
		{
			cerr << "ERROR: That square contains an opponent's checker.\nTry again\n";
			continue;
		}
		if (squarechoice is empty)//no checker at the chosen position
		{
			cerr << "ERROR: That square is empty.\nTry again\n";
			continue;
		}
		if (squarechoice cannot jump, but CountJumps > 0)//if your chosen square can't jump, but another or others can
		{
			cerr << "ERROR: You can jump with another checker, you may not move your chosen checker.\nYou can jump using checkers on the following squares: " << x << y << endl;
			cerr << "Try again\n";
			continue;
		}
		if (squarechoice)//cannot jump or move
		{
			cerr << "ERROR: There is no legal move for this checker.\nTry again\n";
			continue;
		}
}

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int rowsWSoldiers;
	int x;
	int y;
	rowsWSoldiers = (numRowsInBoard / 2) - 1;
	//add the mules in the white side
	for (x = 0; x < numRowsInBoard; x++)
	{
		if (x % 2 != 0)
		{
			CMCheckersBoard[0][x] = WHITEMULE;
		}
		else
		{
			CMCheckersBoard[0][x] = EMPTY;
		}
	}

	//add the white soldiers
	for (y = 1; y < rowsWSoldiers; y++)
	{
		if (y % 2 != 0)//odd row
		{
			for (x = 0; x < numRowsInBoard; x++)
			{
				if (x % 2 != 0)//odd col
				{
					CMCheckersBoard[y][x] = EMPTY;
				}
				else//even col
				{
					CMCheckersBoard[y][x] = WHITESOLDIER;
				}
			}
		}
		else//even row
		{
			for (x = 0; x < numRowsInBoard; x++)
			{ 
				if (x % 2 != 0)//odd col
				{
					CMCheckersBoard[y][x] = WHITESOLDIER;
				}
				else//even col
				{
					CMCheckersBoard[y][x] = EMPTY;
				}
			}
		}
	}
	//two empty rows
	for (y = rowsWSoldiers; y < (rowsWSoldiers + 2); y++)
	{
		for (x = 0; x < numRowsInBoard; x++)
		{
			CMCheckersBoard[y][x] = EMPTY;
		}
	}
	//rows of red soldiers
	for (int y = (rowsWSoldiers + 2); y < (numRowsInBoard - 1); y++)
	{
		if (y % 2 != 0)//odd row
		{
			for (x = 0; x < numRowsInBoard; x++)
			{
				if (x % 2 != 0)//odd col
				{
					CMCheckersBoard[y][x] = EMPTY;
				}
				else//even col
				{
					CMCheckersBoard[y][x] = REDSOLDIER;
				}
			}
		}
		else//even row
		{
			for (x = 0; x < numRowsInBoard; x++)
			{
				if (x % 2 != 0)//odd col
				{
					CMCheckersBoard[y][x] = REDSOLDIER;
				}
				else//even
				{
					CMCheckersBoard[y][x] = EMPTY;
				}
			}
		}
	}
	//row of red mules
	for (x = 0; x < numRowsInBoard; x++)
	{
		if (x % 2 != 0)
		{
			CMCheckersBoard[numRowsInBoard - 1][x] = EMPTY;
		}
		else
		{
			CMCheckersBoard[numRowsInBoard - 1][x] = REDMULE;
		}
	}
}

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	
}




//define the function CountJumps
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
