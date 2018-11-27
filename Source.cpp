/*
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
Authors: Nicholas Hung, Mark Cheng, Eli Planas
☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭☭
*/
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

void getCoordinate(int numRowsInBoard, int input, int xLoc, int yLoc);

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
	}
	if (tries == 3)
	{
		cerr << "ERROR: Too many errors entering the size of the board.";
		return 0;
	}
	InitializeBoard(myCMCheckersBoard, numRowsInBoard);
	DisplayBoard(myCMCheckersBoard, numRowsInBoard);
	//at this point, the board is initialized and game is ready to be played

	player++;
	if (player % 2 != 0)
	{
		player = WHITEPLAYER;
	}
	else
	{
		player = REDPLAYER;
	}

	while (!checkwin)
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
		while (1 == 1)
		{
			cout << "Enter the square number of the checker you want to move\n";
			cin >> checkerMovedstr;
			//chekc the input if it is valid :: it is an int, it is the player's checker, it is in the board
			for (int i = 0; i < checkerMovedstr.size(); i++)
			{
				if (!isdigit(checkerMovedstr.at(i)))
				{
					cerr << "ERROR: You did not enter an integer\nTry again\n";
					continue;
				}
			}
			checkerMoved = stoi(checkerMovedstr);
			if ((checkerMoved > ((numRowsInBoard * numRowsInBoard) - 1)) || checkerMoved < 0)//not located on board!
			{
				cerr << "ERROR: That square is not on the board.\nTry again\n";
				continue;
			}
			getCoordinate(numRowsInBoard, checkerMoved, xInitial, yInitial);
			if (player == WHITEPLAYER)
			{
				if (myCMCheckersBoard[yInitial][xInitial] == REDKING || REDMULE || REDSOLDIER)
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
				else if ((CountJumps(myCMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray) > 0) && !IsJump(myCMCheckersBoard,numRowsInBoard, player, xInitial, yInitial ))
				{
					cerr << "ERROR: You can jump with another checker, you may not move your chosen checker.\nYou can jump using checkers on the following squares: " << x << y << endl;
					cerr << "Try again\n";
					continue;
				}
				else
				{
					break;
				}
			}
			else if (player == WHITEPLAYER)
			{
				if (myCMCheckersBoard[yInitial][xInitial] == WHITEKING || WHITEMULE || WHITESOLDIER)
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
					cerr << "ERROR: You can jump with another checker, you may not move your chosen checker.\nYou can jump using checkers on the following squares: " << x << y << endl;
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
		while ("my ass" == "my ass")
		{
		while ("my ass" == "my ass")
		{
			cout << "Enter the square number of the square you want to move your checker to";
			cin >> checkerPlacedstr;
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
			getCoordinate(numRowsInBoard, checkerPlaced, xFinal, yFinal);
			if (myCMCheckersBoard[xFinal][yFinal] != EMPTY)
			{
				cerr << "ERROR: It is not possible to move to a square that is already occupied.\nTry again";
				continue;
			}
			else if ((myCMCheckersBoard[xFinal][yFinal] == EMPTY) && (IsJump(myCMCheckersBoard, numRowsInBoard, player, xInitial, yInitial)))
			{
				cerr << "ERROR: You can jump with this checker, you must jump not move 1 space.\nTry again";
				continue;
			}
			else
			{
				break;
			}
		}
		makeMove;//determines if the move is legal
		//if it return jump with true

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
				if ((CMCheckersBoard[yIndex][xIndex]) == (REDKING || REDMULE || REDSOLDIER))
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
				if ((CMCheckersBoard[yIndex][xIndex]) == (WHITEKING || WHITEMULE || WHITESOLDIER))
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
			for (yindex = 0; yindex < numRowsInBoard; yindex++)
			{
				for (xindex = 0; xindex < numRowsInBoard; xindex++)
				{
					if ((CMCheckersBoard[yindex][xindex]) == (REDKING || REDMULE || REDSOLDIER))
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
					if ((CMCheckersBoard[yindex][xindex]) == (REDKING || REDMULE || REDSOLDIER))
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

	bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
	{
		if (player == REDPLAYER)//red player
		{
			if (CMCheckersBoard[yLoc][xLoc] == (REDMULE || REDSOLDIER || REDKING))
			{
				if (xLoc == 0)//if on the extreme left
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + (numRowsInBoard - 1)] == WHITEMULE || WHITESOLDIER || WHITEKING)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || WHITESOLDIER || WHITEKING)
					{
						return true;
					}
				}
				if (xLoc == (numRowsInBoard - 1))//if on the extreme right
				{
					if (CMCheckersBoard[yLoc + 1][xLoc - (numRowsInBoard - 1)] == WHITEMULE || WHITESOLDIER || WHITEKING)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || WHITESOLDIER || WHITEKING)
					{
						return true;
					}
				}
				//check if front right/left are available to move to
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || WHITESOLDIER || WHITEKING)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || WHITESOLDIER || WHITEKING)
				{
					return true;
				}

				//check if back right/left are available to move if the checker is a king
				if (CMCheckersBoard[yLoc][xLoc] == (REDKING))
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || WHITESOLDIER || WHITEKING)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || WHITESOLDIER || WHITEKING)
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
					if (CMCheckersBoard[yLoc - 1][xLoc + (numRowsInBoard - 1)] == REDMULE || REDSOLDIER || REDKING)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || REDSOLDIER || REDKING)
					{
						return true;
					}
				}
				if (xLoc == (numRowsInBoard - 1))//if on the extreme right
				{
					if (CMCheckersBoard[yLoc - 1][xLoc - (numRowsInBoard - 1)] == REDMULE || REDSOLDIER || REDKING)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || REDSOLDIER || REDKING)
					{
						return true;
					}
				}
				//check if front right/left are available to move to
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || REDSOLDIER || REDKING)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || REDSOLDIER || REDKING)
				{
					return true;
				}

				//check if back right/left are available to move
				if (CMCheckersBoard[yLoc][xLoc] == (REDKING))
				{
					if (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || REDSOLDIER || REDKING)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || REDSOLDIER || REDKING)
					{
						return true;
					}
				}
			}
		}
	}

	//define the function IsMove1Square
	bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
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

				//check if back right/left are available to move if the checker is a king
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


	//define MakeMove
	//define MakeMove
	bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
	{
		int xdistance = 0;
		int ydistance = 0;
		int xinitial = 0;
		int yinitial = 0;
		int xfinal = 0;
		int yfinal = 0;

		getCoordinate(numRowsInBoard, fromSquareNum, xinitial, yinitial);
		getCoordinate(numRowsInBoard, toSquareNum, xfinal, yfinal);

		xdistance = abs(xfinal - xinitial);
		ydistance = abs(yfinal - yinitial);

		if ((CMCheckersBoard[yinitial][xinitial]) == (WHITESOLDIER)))
		{
			if (xinitial == (numRowsinBoard - 2))
			{
				if ((xfinal == 0) && (ydistance == 2) && (IsJump(CMCheckersBoard, numRowsInBoard, player, xinitial, yinitial)))
				{
					swap((CMCheckers[yinitial][xinitial]), (CMCheckers[yfinal][xfinal]));
					return true;
				}
				else if (ydistance != 2)
				{
					cerr << "ERROR: Illegal move\n";
					return false;
				}
			}
			if (xinitial == (numRowsinBoard - 1))
			{
				if ((xfinal == 0) && (ydistance == 1))
				{
					swap(CMCheckers[yinitial][xinitial], CMCheckers[yfinal][xfinal]);
					return true;
				}
				else if (ydistance != 1)
				{
					cerr << "ERROR: Illegal move\n";
					return false;
				}

				if ((xfinal == 1) && (ydistance == 2))
				{
					swap(CMCheckers[yinitial][xinitial], CMCheckers[yfinal][xfinal]);
					return true;
				}
				else if (ydistance != 2)
				{
					cerr << "ERROR: Illegal move\n";
				}

			}

			if (xinitial == (1))
			{
				if (xfinal ==
			}
		}
		
			
			
			
		if (CMCheckersBoard[yinitial][xinitial] == (REDSOLDIER)


		
		//if x wraps around the left of the board
		if (xinitial == 0)
		{
			if (xfinal == numRowsinBoard && ydistance)
			{

			}
		}
		//xdistance = ydistance
		if (xdistance != ydistance)
		{
			cerr << "ERROR: Illegal move\n";
			return false;
		}

		//if a jump move
		if (ydistance == 2 && xdistance == 2)
		{
			return true;
		}
		//if a step move
		if (ydistance == 1 && xdistance == 1)
		{
			return false;
		}
	
	}
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
	
bool CheckWin() //not sure which data type i should be using here, since it's returning true or false i THINK 
                //this should be right...
{


	int redSOLDIERcount = 0;
	int redKINGcount = 0;
	int redMULEcount = 0;
	int whiteSOLDIERcount = 0;
	int whiteKINGcount = 0;
	int whiteMULEcount = 0;

	for (i = 0, i < numRowsInBoard, i++)
	{
		for (j = 0, j < numRowsInBoard, j++)
		{
			if (CMCheckersBoard[i][j] == REDSOLDIER)
			{
				redSOLDIERcount++
			}
			else if (CMCheckersBoard[i][j] == REDKING)
			{
				redKINGcount++
			}
			else if (CMCheckersBoard[i][j] == REDMULE)
			{
				redMULEcount++
			}
			else if (CMCheckersBoard[i][j] == WHITESOLDIER)
			{
				whiteSOLDIERcount++
			}
			else if (CMCheckersBoard[i][j] == WHITEKING)
			{
				whiteKINGcount++
			}
			else if (CMCheckersBoard[i][j] == WHITEMULE)
			{
				whiteMULEcount++
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
	else               //if none of the above 4 conditions are met...
		return false;

	return;
}
