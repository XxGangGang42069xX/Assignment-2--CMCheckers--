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

void getCoordinate(int numRowsInBoard, int input, int xLoc, int yLoc);

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
const int EMPTY = 0;

//for displaying the pieces
const string WHITESOLDIERSTR = "WS";
const string WHITEMULESTR = "WM";
const string WHITEKINGSTR = "WK";
const string REDSOLDIERSTR = "RS";
const string REDMULESTR = "RM";
const string REDKINGSTR = "RK";
const string EMPTYSTR = "0";

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
	int lol;
	int lel;

	numRowsInBoard = 0;
	MAXtries = 3;
	
	//initialize this array to all 0s
	for (lol = 0; lol < MAX_ARRAY_SIZE; lol++)
	{
		for (lel = 0; lel < MAX_ARRAY_SIZE; lel++)
		{
			myCMCheckersBoard[lol][lel] = 0, 0;
		}
	}
	
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
	//at this point, the board is initialized and game is ready to be played

	player = WHITEPLAYER;
	while (!checkwin)
	{
		if (CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) == 0 && CountJumps(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) == 0)
		{
			//player can't do any moves opposing player wins
			/*White/red is unable to move.

			GAME OVER, Red/white has won.

			Enter any character to close the game.*/
		}
		if (player == WHITEPLAYER)
		{
			cout << "White takes a turn.\n";
		}
		else
		{
			cout << "Red takes a turn.\n";
		}
		//prompt for which checker to move
		cout << "Enter the square number of the checker you want to move\n";
		cin >> checkerMoved;
		//chekc the input if it is valid :: it is an int, it is the player's checker, it is in the board
	}
	
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
	int spotCounter;
	spotCounter = 0;
	for (int y = 0; y < numRowsInBoard; ++y)
	{
		for (int x = 0; x < numRowsInBoard; ++x)
		{
			
			//cout << CMCheckersBoard[y][x] << " ";
			switch (CMCheckersBoard[y][x]) 
			{
				case EMPTY:
				{
					cout << setw(4) << spotCounter;
					break;
				}
				case WHITESOLDIER:
				{
					cout << setw(4) << WHITESOLDIERSTR;
					break;
				}
				case WHITEMULE:
				{
					cout << setw(4) << WHITEMULESTR;
					break;
				}
				case WHITEKING:
				{
					cout << setw(4) << WHITEKINGSTR;
					break;
				}
				case REDSOLDIER:
				{
					cout << setw(4) << REDSOLDIERSTR;
					break;
				}
				case REDMULE:
				{
					cout << setw(4) << REDMULESTR;
					break;
				}
				case REDKING:
				{
					cout << setw(4) << REDKINGSTR;
					break;
				}
			}
			spotCounter++;
		}
		cout << endl;
	}
	cout << endl << endl << endl;
}

void getCoordinate(int numRowsInBoard, int input, int xLoc, int yLoc)
{
	int yLoc = 0;
	int xLoc = 0;

	yLoc = input / numRowsInBoard;
	xLoc = input - (yLoc * numRowsInBoard);

	//cout << numRowsInBoard << input << endl << xLoc << endl << yLoc;

}


//define the function CountJumps
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
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
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
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
//define the function IsMove1Square
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == REDPLAYER)//red player
	{
		if (CMCheckersBoard[yLoc][xLoc] == (REDMULE || REDSOLDIER || REDKING))
		{
			if (xLoc == 0)//if on the extreme left
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + (numRowsInBoard - 1)] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == EMPTY)
				{
					return true;
				}
			}
			if (xLoc == (numRowsInBoard - 1))//if on the extreme right
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - (numRowsInBoard - 1)] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == EMPTY)
				{
					return true;
				}
			}
			//check if front right/left are available to move to
			if (CMCheckersBoard[yLoc + 1][xLoc + 1] == EMPTY)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == EMPTY)
			{
				return true;
			}

			//check if back right/left are available to move
			if (CMCheckersBoard[yLoc][xLoc] == (REDKING))
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == EMPTY)
				{
					return true;
				}
			}
		}
	}

	if (player == WHITEPLAYER)//white player
	{
		if (CMCheckersBoard[yLoc][xLoc] == (WHITEMULE || WHITESOLDIER || WHITEKING))
		{
			if (xLoc == 0)//if on the extreme left
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + (numRowsInBoard - 1)] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == EMPTY)
				{
					return true;
				}
			}
			if (xLoc == (numRowsInBoard - 1))//if on the extreme right
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - (numRowsInBoard - 1)] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == EMPTY)
				{
					return true;
				}
			}
			//check if front right/left are available to move to
			if (CMCheckersBoard[yLoc - 1][xLoc + 1] == EMPTY)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == EMPTY)
			{
				return true;
			}

			//check if back right/left are available to move
			if (CMCheckersBoard[yLoc][xLoc] == (REDKING))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == EMPTY)
				{
					return true;
				}
			}
		}
	}
}



