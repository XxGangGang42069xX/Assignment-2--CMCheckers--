#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

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
const int EMPTY = 0;

//for displaying the pieces
const string WHITESOLDIERSTR = "WS";
const string WHITEMULESTR = "WM";
const string WHITEKINGSTR = "WK";
const string REDSOLDIERSTR = "RS";
const string REDMULESTR = "RM";
const string REDKINGSTR = "RK";
const string EMPTYSTR = "0";

//function prototypes
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

int getyCoordinate(int numRowsInBoard, int input);

int getxCoordinate(int numRowsInBoard, int input, int yLoc);

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int main()
{
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {};
	int xIndicesMove[MAX_PIECES] = {};
	int yIndicesMove[MAX_PIECES] = {};
	int xIndicesJump[MAX_PIECES] = {};
	int yIndicesJump[MAX_PIECES] = {};
	int xLocArray[MAX_ARRAY_SIZE] = {};
	int yLocArray[MAX_ARRAY_SIZE] = {};
	string numRowsInBoardstr;
	int numRowsInBoard;
	int tries;
	int MAXtries;
	int lol;
	int lel;
	int player;
	string checkerMovedstr;
	int checkerMoved;
	string checkerPlacedstr;
	int checkerPlaced;
	int xInitial;
	int yInitial;
	int xFinal;
	int yFinal;
	bool didthischekcerjump;
	bool diditjump;

	numRowsInBoard = 0;
	MAXtries = 3;
	player = 0;
	checkerMoved = 0;
	xInitial = 0;
	yInitial = 0;
	xFinal = 0;
	yFinal = 0;


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
				goto lalala;
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
		else if (numRowsInBoard < MIN_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too small.\n8 <= number of squares <= 18\n";
			continue;
		}
		else if (numRowsInBoard > MAX_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too large.\n8 <= number of squares <= 18\n";
			continue;
		}
		else
		{
			// it is an integer
			break;
		}
		lalala:;
	}
	if (tries == 3)
	{
		cerr << "ERROR: Too many errors entering the size of the board.";
		return 0;
	}

	InitializeBoard(myCMCheckersBoard, numRowsInBoard);
	DisplayBoard(myCMCheckersBoard, numRowsInBoard);
	//at this point, the board is initialized and game is ready to be played

	player = WHITEPLAYER;

	while (!CheckWin(myCMCheckersBoard, numRowsInBoard))
	{
		if (CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) == 0 && CountJumps(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) == 0)
		{
			//player can't do any moves opposing player wins
			/*White/red is unable to move.
			GAME OVER, Red/white has won.
			Enter any character to close the game.
			//the player has no more moves = he loses
			cout << "White is unable to move.\nGAME OVER, Red has won.\nEnter any character to close the game.";
			return 0;
			*/
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
		while (!CheckWin(myCMCheckersBoard, numRowsInBoard))
		{
			redo:
			cout << "Enter the square number of the checker you want to move\n";
			cin >> checkerMovedstr;
			//check the input if it is valid :: it is an int, it is the player's checker, it is in the board
			for (int i = 0; i < checkerMovedstr.size(); i++)
			{
				if (!isdigit(checkerMovedstr.at(i)))
				{
					cerr << "ERROR: You did not enter an integer\nTry again\n";
					goto redo;
				}
			}
			checkerMoved = stoi(checkerMovedstr);
			if ((checkerMoved > ((numRowsInBoard * numRowsInBoard) - 1)) || checkerMoved < 0)//not located on board!
			{
				cerr << "ERROR: That square is not on the board.\nTry again\n";
				continue;
			}
			yInitial = getyCoordinate(numRowsInBoard, checkerMoved);
			xInitial = getxCoordinate(numRowsInBoard, checkerMoved, yInitial);

			if (player == WHITEPLAYER)
			{
				if (myCMCheckersBoard[yInitial][xInitial] == REDKING || myCMCheckersBoard[yInitial][xInitial] == REDMULE || myCMCheckersBoard[yInitial][xInitial] == REDSOLDIER)
				{
					cerr << "ERROR: That square contains an opponent's checker.\nTry again\n";
					continue;
				}
				else if (myCMCheckersBoard[yInitial][xInitial] == EMPTY)
				{
					cerr << "ERROR: That square is empty.\nTry again\n";
					continue;
				}
				else if ((!IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial) && (!IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial))))
				{
					cerr << "ERROR: There is no legal move for this checker.\nTry again\n";
					continue;
				}
				else if ((CountJumps(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) > 0) && !IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial))
				{
					cerr << "ERROR: You can jump with another checker, you may not move your chosen checker.\nYou can jump using checkers on the following squares: " << /*x << y << */endl;
					cerr << "Try again\n";
					continue;
				}
				else
				{
					break;
				}
			}
			else if (player == REDPLAYER)
			{
				if (myCMCheckersBoard[yInitial][xInitial] == WHITEKING || myCMCheckersBoard[yInitial][xInitial] == WHITEMULE || myCMCheckersBoard[yInitial][xInitial] == WHITESOLDIER)
				{
					cerr << "ERROR: That square contains an opponent's checker.\nTry again\n";
					continue;
				}
				else if (myCMCheckersBoard[yInitial][xInitial] == EMPTY)
				{
					cerr << "ERROR: That square is empty.\nTry again\n";
					continue;
				}
				else if ((!IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial) && (!IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial))))
				{
					cerr << "ERROR: There is no legal move for this checker.\nTry again\n";
					continue;
				}
				else if ((CountJumps(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) > 0) && !IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial))
				{
					cerr << "ERROR: You can jump with another checker, you may not move your chosen checker.\nYou can jump using checkers on the following squares: " <</* x << y <<*/ endl;
					cerr << "Try again\n";
					continue;
				}
				else
				{
					break;
				}
			}
		}
		//prompt for the square the checker is moving to
		while (!CheckWin(myCMCheckersBoard, numRowsInBoard))
		{
		righthere:
			cout << "Enter the square number of the square you want to move your checker to\n";
			jumparound:
			cin >> checkerPlacedstr;
			cout << endl;
			for (int i = 0; i < checkerPlacedstr.size(); i++)
			{
				if (!isdigit(checkerPlacedstr.at(i)))
				{
					cerr << "ERROR: You did not enter an integer\nTry again\n";
					continue;
				}
			}
			checkerPlaced = stoi(checkerPlacedstr);
			if ((checkerPlaced > ((numRowsInBoard * numRowsInBoard) - 1)) || checkerPlaced < 0)//not located on board!
			{
				cerr << "ERROR: That square is not on the board.\nTry again\n";
				continue;
			}

			yFinal = getyCoordinate(numRowsInBoard, checkerPlaced);
			xFinal = getxCoordinate(numRowsInBoard, checkerPlaced, yFinal);

			if (myCMCheckersBoard[yFinal][xFinal] != EMPTY)//there is a checker there
			{
				cerr << "ERROR: It is not possible to move to a square that is already occupied.\nTry again\n";
				continue;
			}		
			else if ((myCMCheckersBoard[yFinal][xFinal] == EMPTY) && (IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial)) && (abs(yFinal - yInitial) == 1))
			{																																				
				cerr << "ERROR: You can jump with this checker, you must jump not move 1 space.\nTry again\n";
				continue;
			}
			else
			{
				break;
			}
		}

		//determines if the move is legal
		//if it returns *jump with true, you jumped niBBA, do it again if you can
		bool diditjump = IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial);
		bool diditmove = MakeMove(myCMCheckersBoard, numRowsInBoard, player, checkerMoved, checkerPlaced, didthischekcerjump);

		if (!(diditmove))
		{
			goto righthere;
		}
		else
		{
			if (didthischekcerjump)
			{
				DisplayBoard(myCMCheckersBoard, numRowsInBoard);
				if (diditjump)
				{
					if (IsJump(myCMCheckersBoard, numRowsInBoard, player, xFinal, yFinal))
					{
						cout << "You can jump again, Please enter the next square you wish to move your checker to\n";
						checkerMoved = checkerPlaced;
						goto jumparound;
					}
				}



				if (player == WHITEPLAYER)
				{
					player = REDPLAYER;
				}
				else if (player == REDPLAYER)
				{
					player = WHITEPLAYER;
				}
				continue;
			}
		}
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

int getyCoordinate(int numRowsInBoard, int input)
{
	int yLoc = 0;
	yLoc = input / numRowsInBoard;
	return yLoc;
}

int getxCoordinate(int numRowsInBoard, int input, int yLoc)
{
	int xLoc = 0;
	xLoc = input - (yLoc * numRowsInBoard);
	return xLoc;
}

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	//declare all local variables
	int jumps = 0;
	int i = 0;
	int xIndex = 0;
	int yIndex = 0;
	//initialize all elements of yLocArray and xLocaray to -1
	for (i = 0; i < MAX_PIECES; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}
	if (player == REDPLAYER) //red players
	{
		for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
		{
			for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
			{
				if ((CMCheckersBoard[yIndex][xIndex]) == REDKING || (CMCheckersBoard[yIndex][xIndex]) == REDMULE || (CMCheckersBoard[yIndex][xIndex]) == REDSOLDIER)
				{
					if (IsJump(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex))
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
	if (player == WHITEPLAYER) //white players
	{
		for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
		{
			for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
			{
				if ((CMCheckersBoard[yIndex][xIndex]) == WHITEKING || (CMCheckersBoard[yIndex][xIndex]) == WHITEMULE || (CMCheckersBoard[yIndex][xIndex]) == WHITESOLDIER)
				{
					if (IsJump(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex))
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

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == REDPLAYER)//red player
	{
		if (CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			if (yLoc == 1)
			{
				return false;
			}
			if (CMCheckersBoard[yLoc][xLoc] == REDKING)
			{
				if (yLoc == (numRowsInBoard - 2))
				{
					return false;
				}
			}
			if (xLoc == 0)//if on the extreme left
			{
				if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc + 2] == EMPTY)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc + 2] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == EMPTY)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			if (xLoc == (numRowsInBoard - 1))//if on the extreme right
			{
				if (CMCheckersBoard[yLoc - 1][0] == WHITEMULE || CMCheckersBoard[yLoc - 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][0] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][1] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 1][0] == WHITEMULE || CMCheckersBoard[yLoc + 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][0] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][1] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc - 2] == EMPTY)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == (numRowsInBoard - 2))// second from the right
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][0] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][0] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc - 2] == EMPTY)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc + 2] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING)
					{
						if (CMCheckersBoard[yLoc + 2][xLoc - 2] == EMPTY)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
				}
			}
		}
	}

	if (player == WHITEPLAYER)//white player
	{
		if (CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{
			if (yLoc == (numRowsInBoard - 2))
			{
				return false;
			}
			if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
			{
				if (yLoc == 2)
				{
					return false;
				}
			}
			if (xLoc == 0)//if on the extreme left
			{
				if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc + 2] == EMPTY)
						{
							return true;
						}
					}
				}
				return false;

			}
			else if (xLoc == 1)// second spot from left
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc + 2] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == EMPTY)
						{
							return true;
						}
					}
				}
				return false;
			}
			else if (xLoc == (numRowsInBoard - 1))//if on the extreme right
			{
				if (CMCheckersBoard[yLoc + 1][0] == REDMULE || CMCheckersBoard[yLoc + 1][0] == REDSOLDIER || CMCheckersBoard[yLoc + 1][0] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][1] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 1][0] == REDMULE || CMCheckersBoard[yLoc - 1][0] == REDSOLDIER || CMCheckersBoard[yLoc - 1][0] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][1] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc - 2] == EMPTY)
						{
							return true;
						}
					}
				}
				return false;
			}
			else if (xLoc == (numRowsInBoard - 2))// second from the right
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][0] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][0] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc - 2] == EMPTY)
						{
							return true;
						}
					}
					return false;

				}
			}
			else // normal situation
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == EMPTY)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc + 2] == EMPTY)
						{
							return true;
						}
					}
					if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING)
					{
						if (CMCheckersBoard[yLoc - 2][xLoc - 2] == EMPTY)
						{
							return true;
						}
					}
				}
				return false;

			}
		}
		return false;
	}
}

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
		for (yindex = 0; yindex < numRowsInBoard; yindex++)
		{
			for (xindex = 0; xindex < numRowsInBoard; xindex++)
			{
				if ((CMCheckersBoard[yindex][xindex]) == REDKING || (CMCheckersBoard[yindex][xindex]) == REDMULE || (CMCheckersBoard[yindex][xindex]) == REDSOLDIER)
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xindex, yindex) == true)
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
		for (yindex = 0; yindex < numRowsInBoard; yindex++)
		{
			for (xindex = 0; xindex < numRowsInBoard; xindex++)
			{
				if ((CMCheckersBoard[yindex][xindex]) == REDKING || (CMCheckersBoard[yindex][xindex]) == REDMULE || (CMCheckersBoard[yindex][xindex]) == REDSOLDIER)
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xindex, yindex) == true)
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

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == REDPLAYER)//red player
	{
		if (CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDKING)
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
			if (CMCheckersBoard[yLoc - 1][xLoc + 1] == EMPTY)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == EMPTY)
			{
				return true;
			}
			//check if back right/left are available to move if the checker is a king
			if (CMCheckersBoard[yLoc][xLoc] == (REDKING))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == EMPTY)
				{
					return true;
				}
			}
			return false;
		}
	}

	if (player == WHITEPLAYER)//white player
	{
		if (CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEKING)
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
			if (CMCheckersBoard[yLoc + 1][xLoc + 1] == EMPTY)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == EMPTY)
			{
				return true;
			}
			//check if back right/left are available to move
			if (CMCheckersBoard[yLoc][xLoc] == (WHITEKING))
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == EMPTY)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == EMPTY)
				{
					return true;
				}
			}
			return false;
		}
	}
}

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	int xdistance = 0;
	int ydistance = 0;
	int ydirection = 0;
	int xdirection = 0;
	int xinitial = 0;
	int yinitial = 0;
	int xfinal = 0;
	int yfinal = 0;
	string endgame;

	yinitial = getyCoordinate(numRowsInBoard, fromSquareNum);
	xinitial = getxCoordinate(numRowsInBoard, fromSquareNum, yinitial);
	yfinal = getyCoordinate(numRowsInBoard, toSquareNum);
	xfinal = getxCoordinate(numRowsInBoard, toSquareNum, yfinal);

	//getCoordinate(numRowsInBoard, fromSquareNum, xinitial, yinitial);
	//getCoordinate(numRowsInBoard, toSquareNum, xfinal, yfinal);

	xdistance = abs(xfinal - xinitial);//distance of x
	ydistance = abs(yfinal - yinitial);//distance of y
	ydirection = yfinal - yinitial;//with neg val
	xdirection = xfinal - xinitial;//with neg val

	if (((CMCheckersBoard[yinitial][xinitial]) == REDKING) || ((CMCheckersBoard[yinitial][xinitial]) == WHITEKING) || ((CMCheckersBoard[yinitial][xinitial]) == REDSOLDIER) || ((CMCheckersBoard[yinitial][xinitial]) == WHITESOLDIER) || ((CMCheckersBoard[yinitial][xinitial]) == REDMULE) || ((CMCheckersBoard[yinitial][xinitial]) == WHITEMULE))
	{
		//if xinitial is on the right second space
		if (xinitial == (numRowsInBoard - 2) && (xfinal == 0) && (ydistance == 2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))//legal move ;; return true
		{
			//white soldiers and white mules
			if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
			{
				if (ydirection < 0)
				{
					//WRONG WAAY ERROR
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			//red soldiers and red mules
			if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
			{
				if (ydirection > 0)
				{
					//wrong way error
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			if (ydirection < 0)//red something
			{
				swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
				CMCheckersBoard[yinitial - 1][xinitial + 1] = EMPTY;
				if (yfinal == 0)
				{
					if (CMCheckersBoard[yinitial][xinitial] == REDMULE)
					{
						cout << "Red has created a Mule King, White wins the game\n";
						cout << "Enter any character to terminate the game then press the enter key\n";
						cin >> endgame;
						return 0;
						//game over
					}
					if (CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
					{
						CMCheckersBoard[yfinal][xfinal] = REDKING;
					}
				}
				return true;
			}
			if (ydirection > 0)//white something
			{
				swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
				CMCheckersBoard[yinitial + 1][xinitial + 1] = EMPTY;
				if (yfinal == (numRowsInBoard - 1))
				{
					if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE)
					{
						cout << "White has created a Mule King, Red wins the game\n";
						cout << "Enter any character to terminate the game then press the enter key\n";
						cin >> endgame;
						return 0;
						//game over
					}
					if (CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
					{
						CMCheckersBoard[yfinal][xfinal] = WHITEKING;
					}
				}
				return true;
			}
			/*if ((xfinal == 0) && (ydirection == -2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))
			{
				swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
				return true;
			}
			else if (ydirection != -2)
			{
				cerr << "ERROR: Illegal move\n";
				return false;
			}*/
		}
		//if x initial is on the very far right
		else if (xinitial == (numRowsInBoard - 1) && ((xdistance != 1) && (xdistance != 2)))
		{
			if ((xfinal == 0) && (ydistance == 1))
			{
				if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
				{
					if (ydirection < 0)
					{
						//WRONG WAAY ERROR
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				//red soldiers and red mules
				if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
				{
					if (ydirection > 0)
					{
						//wrong way error
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				swap(CMCheckersBoard[yinitial][xinitial], CMCheckersBoard[yfinal][xfinal]);
				return true;
			}
			else if ((xfinal == 1) && (ydistance == 2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))
			{
				if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
				{
					if (ydirection < 0)
					{
						//WRONG WAAY ERROR
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				//red soldiers and red mules
				if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
				{
					if (ydirection > 0)
					{
						//wrong way error
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				if (ydirection < 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial - 1][xfinal - 1] = EMPTY;
					return true;
				}
				if (ydirection > 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial + 1][xfinal - 1] = EMPTY;
					return true;
				}
			}
		}
		//second from the left
		else if (xinitial == (1) && (xfinal == numRowsInBoard - 1) && (ydistance == 2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))//legal move ;; return true
		{
			if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
			{
				if (ydirection < 0)
				{
					//WRONG WAAY ERROR
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			//red soldiers and red mules
			if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
			{
				if (ydirection > 0)
				{
					//wrong way error
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			if (ydirection < 0)
			{
				swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
				CMCheckersBoard[yinitial - 1][xinitial - 1] = EMPTY;
				return true;
			}
			if (ydirection > 0)
			{
				swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
				CMCheckersBoard[yinitial + 1][xinitial - 1] = EMPTY;
				return true;
			}
		}
		//extreme left
		else if (xinitial == (0) && ((xdistance != 1) && (xdistance != 2)))
		{
			if ((xfinal == numRowsInBoard - 1) && (ydistance == 1))
			{
				if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
				{
					if (ydirection < 0)
					{
						//WRONG WAAY ERROR
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				//red soldiers and red mules
				if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
				{
					if (ydirection > 0)
					{
						//wrong way error
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				swap(CMCheckersBoard[yinitial][xinitial], CMCheckersBoard[yfinal][xfinal]);
				return true;
			}
			else if ((xfinal == (numRowsInBoard - 2)) && (ydistance == 2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))
			{
				if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
				{
					if (ydirection < 0)
					{
						//WRONG WAAY ERROR
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				//red soldiers and red mules
				if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
				{
					if (ydirection > 0)
					{
						//wrong way error
						cerr << "ERROR: Illegal move\n";
						return false;
					}
				}
				if (ydirection < 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial - 1][xfinal + 1] = EMPTY;
					return true;
				}
				if (ydirection > 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial + 1][xfinal + 1] = EMPTY;
					return true;
				}
			}
		}
		//normal situation
		else if ((ydistance == 2) && (xdistance == 2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))
		{
			if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
			{
				if (ydirection < 0)
				{
					//WRONG WAAY ERROR
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			//red soldiers and red mules
			if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
			{
				if (ydirection > 0)
				{
					//wrong way error
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			if (ydirection < 0)
			{
				if (xdirection < 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial - 1][xinitial - 1] = EMPTY;
					return true;
				}
				else if (xdirection > 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial - 1][xinitial + 1] = EMPTY;
					return true;
				}
			}
			if (ydirection > 0)
			{
				if (xdirection < 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial + 1][xinitial - 1] = EMPTY;
					return true;
				}
				else if (xdirection > 0)
				{
					swap((CMCheckersBoard[yinitial][xinitial]), (CMCheckersBoard[yfinal][xfinal]));
					CMCheckersBoard[yinitial + 1][xinitial + 1] = EMPTY;
					return true;
				}
			}
		}
		//another normie
		else if ((ydistance == 1) && (xdistance == 1))
		{
			//white s and white m
			if (CMCheckersBoard[yinitial][xinitial] == WHITEMULE || CMCheckersBoard[yinitial][xinitial] == WHITESOLDIER)
			{
				if (ydirection < 0)
				{
					//WRONG WAAY ERROR
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			//red soldiers and red mules
			if (CMCheckersBoard[yinitial][xinitial] == REDMULE || CMCheckersBoard[yinitial][xinitial] == REDSOLDIER)
			{
				if (ydirection > 0)
				{
					//wrong way error
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			swap(CMCheckersBoard[yinitial][xinitial], CMCheckersBoard[yfinal][xfinal]);
			return true;
		}
		else
		{
			return false;
		}


	}
}

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int redSOLDIERcount = 0;
	int redKINGcount = 0;
	int redMULEcount = 0;
	int whiteSOLDIERcount = 0;
	int whiteKINGcount = 0;
	int whiteMULEcount = 0;

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			if (CMCheckersBoard[i][j] == REDSOLDIER)
			{
				redSOLDIERcount++;
			}
			else if (CMCheckersBoard[i][j] == REDKING)
			{
				redKINGcount++;
			}
			else if (CMCheckersBoard[i][j] == REDMULE)
			{
				redMULEcount++;
			}
			else if (CMCheckersBoard[i][j] == WHITESOLDIER)
			{
				whiteSOLDIERcount++;
			}
			else if (CMCheckersBoard[i][j] == WHITEKING)
			{
				whiteKINGcount++;
			}
			else if (CMCheckersBoard[i][j] == WHITEMULE)
			{
				whiteMULEcount++;
			}
		}
	}
	if (redMULEcount == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules";
		return true;
	}
	else if (whiteMULEcount == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules";
		return true;
	}
	else if (redSOLDIERcount == 0 && redKINGcount == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings";
		return true;
	}
	else if (whiteSOLDIERcount == 0 && whiteKINGcount == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings";
		return true;
	}
	else     //if none of the above 4 conditions are met...
	{
		return false;
	}
}
