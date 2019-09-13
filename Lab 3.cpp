/* Lab 3.
Mauricio Fossas Koval
mauricio.fossas@wustl.edu
Defines all functions of class TicTacToeGame. Takes in one argument, which should be the game to play, 
TicTacToe, and allows user to choose weather X or O can start, and gives the option to quit mid game. 
Detects a winner as soon as someone gets 3 in a row, but detects ties only until board is filled and there 
is no winner. 
Extra credit: auto_player() makes one of the players the computer (X) and once there is an opportunity to win
(2 X's in a row) it plays the next square to win, and if there is an oportunity to block (2 O's in a row)
it blocks the user.
*/

#include "stdafx.h"
#include "TicTacToe.h"
#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <sstream>

using namespace std;


int main(int argc, char * argv[])
{
	string s;
	string s2;
	if (argc == numarguments)
	{
		s = argv[cmdLineArg];
	}
	if (argc == numargsWExtraCredit)
	{
		s = argv[cmdLineArg];
		s2 = argv[numarguments];
	}
	if ((argc == numarguments) && (s == "TicTacToe"))
	{
		TicTacToeGame game;
		return game.play();
	}
	if ((argc == numargsWExtraCredit) && (s == "TicTacToe") && (s2 == "auto_player"))
	{
		TicTacToeGame game;
		return game.autoplayer();
	}
	return usageMessage(argv[programName]);
}

//Constructor: builds the board to be of size rows*columns
TicTacToeGame::TicTacToeGame() 
{
	for (int i = 0; i < rows; ++i)
	{
		for (int x = 0; x < columns; ++x)
		{
			board.push_back(" ");
		}
	}
}

ostream &operator << (ostream &output, TicTacToeGame &game) 
{
	//Prints the board top to bottom...
	for (int i = (game.rows - 1); i >= 0; --i)
	{
		if (i < 0)
		{
			break;
		}
		//...and left to right...
		for (int x = 0; x < game.columns; ++x)
		{
			int index = (game.columns)* i + x;
			//If the column is 0, it prints out the row (not part of the board)
			if (x == 0)
			{
				output << i;
			}
			output << game.board[index] << "|";
		}
		output << endl;
		output << " ----------" << endl;
	}
	//After printing out the board we print out the rows at the very bottom
	output << " ";
	for (int w = 0; w < game.columns; ++w)
	{
		output << w << " ";
	}
	output << endl;
	return output;
} 

bool TicTacToeGame::done()
{
	//Checking for vertical winners. Indices 6,11,16 map to (1,1), (2,1), (3,1) respectively and so on...
	for (int i = 0; i < 3; ++i)
	{
		if (board[6 + i] != " ") 
		{
			if (board[6 + i] == board[11 + i])
			{
				if (board[11 + i] == board[16 + i])
				{
					winner = board[11 + i];
					return true;
				}
			}
		}
	}
	//Checking for horizontal winners. Indices 6,7,8 map to (1,1), (1,2), and (1,3) respectively and so on...
	for (int i = 0; i < 11; i = i + 5)
	{
		if (board[6 + i] != " ")
		{
			if (board[6 + i] == board[7 + i])
			{
				if (board[7 + i] == board[8 + i])
				{
					winner = board[8 + i];
					return true;
				}
			}
		}
	}
	//Checking the diagonal
	if (board[12] != " ")
	{
		if (board[12] == board[6])
		{
			if (board[6] == board[18])
			{
				winner = board[12];
				return true;
			}
		}
		if (board[12] == board[16])
		{
			if (board[16] == board[8])
			{
				winner = board[12];
				return true;
			}
		}
	}
	return false;
}

bool TicTacToeGame::draw()
{
	if (done() == true || moves < 9)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int TicTacToeGame::prompt(unsigned int &row, unsigned int &col) {
	cout << "Provide a position to place your piece in the following format: " << endl;
	cout << "row,column. Where row and column have to be greater than or equal to 1 and less than or equal to 3." << endl;
	cout << "Or enter quit if you wish to quit the game." << endl;
	string read;
	while(cin >> read)
	{
		//If the first character of our string is an alphabetical character, then the user must have inputed
		//either quit or a non-valid input. 
		if (isalpha(read[0]))
		{
			//Converting read to all lower case alphas
			lowerCaseStings(read);
			//If the string does not equal quit, we want to rempromt the user to enter a valid input.
			if (read != "quit")
			{
				//Prompting the user for valid input; which brings us back to the while loop.
				cout << "Please provide a VALID input." << endl;
			}
			else
			{
				return quit;
			}
		}
		//If the first character is not an alphabetical character then it must be either unvalid or a valid
		//input for pieces.
		else
		{
			//If the input is in the form row,column where row and column <=3 and >=1 then the string should be
			//of length 3 including the comma and the string[0] and at [2] 
			if (read.length() == 3 && isdigit(read[0]) && isdigit(read[2]) && read[1] == ',')
			{
				//Replacing the comma for a whitespace to be able to extract the values using istringstream
				read[1] = ' ';
				istringstream stream(read);
				stream >> row;
				stream >> col;
				//Checking that row and column are between 1 and 3 inclusive.
				if (row > 0 && col > 0 && row < 4 && col < 4)
				{
					return success;
				}
				else
				{
					cout << "Please provide a VALID input" << endl;
				}
			}
			//If the length of the string was not 3 or the 1st and 3rd entry were not digits or the 2nd entry was 
			//not a comma then we want to reprompt the user for valid input.
			else
			{
				cout << "Please provide a VALID input" << endl;
			}
		}
	}
	//It should never reach this return. 
	return error;
}

//Method that converts a string to all lowercase.
string lowerCaseStings(string & word)
{
	for (unsigned int i = 0; i < word.length(); ++i)
	{
		//Checking to see if the character falls (in integer value) between A and Z
		if ((int)word[i] >= (int)'A' && (int)word[i] <= (int)'Z')
		{
			//Make the character at this location the character for the value of adding 32 to the former character
			word[i] = char((int)word[i] + 32);
		}
		else
		{
			word[i] = word[i];
		}
	}
	return word;
}

int TicTacToeGame::turn()
{
	unsigned int ro, co;
	unsigned int index;
	string tempCheck;
	if (moves == 0 && XorO == "empty")
	{
		cout << "Would you want X's or O's to start? You may also enter quit to exit." << endl;
		while (cin >> tempCheck)
		{
			if (tempCheck == "X" || tempCheck == "O")
			{
				XorO = tempCheck;
				break;
			}
			else
			{
				lowerCaseStings(tempCheck);
				if (tempCheck == "quit")
				{
					return quit;
				}
				else
				{
					cout << "Please provide valid input. Make sure you are providing an upper case X or O." << endl;
				}
			}
		}
	}
	cout << "Player " << XorO << ": " << endl;
	if (prompt(ro, co) == quit)
	{
		return quit;
	}
	else
	{
		index = columns*ro + co;
		if (board[index] != " ")
		{
			cout << " " << endl;
			cout << "There is already a piece at the given location, please try again" << endl;
			return turn();
		}
		else
		{
			board[index] = XorO;
			++moves;
			if (XorO == "X")
			{
				Xmoves += to_string(ro) + ", " +  to_string(co) + "; ";
				XorO = "O";
			}
			else
			{
				Omoves += to_string(ro) + ", " + to_string(co) + "; " ;
				XorO = "X";
			}
			return success;
		}
	}
}

int TicTacToeGame::play()
{
	while (moves < 9)
	{
		cout << *this << endl;
		cout << Xmoves << endl;
		cout << Omoves << endl;
		if (turn() == quit)
		{
			cout << "You have quit the game. " << moves << " moves were played." << endl;
			return quit;
		}
		if (done() == true)
		{
			cout << *this << endl;
			cout << "Congratulations, player " << winner << " won after " << moves << " moves" << endl;
			return success;
		}
		if (draw() == true)
		{
			cout << *this << endl;
			cout << "You drew." << endl;
			return tie;
		}
	}
	return success;
}

int usageMessage(char * program)
{
	cout << "Incorrect number or format of command line arguments, expected " << cmdLineArg << " or " << numarguments << " command line arguments where the first one should be: TicTacToe ";
		cout << "and if you wish to play against a computer, the second argument should be: auto_player" << endl;
	return wrongCmdLineArgs;
}

//Extra credit:
int TicTacToeGame::autoplayer()
{
	string start;
	cout << "Type X if you would want the computer to start, or O if you wish to start. If you wish to exit type quit." << endl;
	cin >> start;
	if (start == "X" || start == "O")
	{
		XorO = start;
	}
	else
	{
		lowerCaseStings(start);
		if (start == "quit")
		{
			cout << "You have quit the game." << endl;
			return quit;
		}
		else
		{
			cout << "Please provide a VALID input. Make sure you are providing an upper case X (cpu) or O (user)." << endl;
			return autoplayer();
		}
	}
	while (moves < 9)
	{
		//Computer starts first move.
		if (moves == 0 && XorO == "X")
		{
			//There is technically no better first move in tictactoe, but common strategies suggest to start
			//by placing a piece in a corner.
			board[6] = "X";
			XorO = "O";
			moves = moves + 1;
		}
		//Player starts with first move
		if (moves == 0 && XorO == "O")
		{
			cout << *this << endl;
			if (turn() == quit)
			{
				cout << "You have quit the game. " << moves << " moves were played." << endl;
				return quit;
			}
		}
		//Players move (same as our play method).
		if (XorO == "O" && moves > 0)
		{
			cout << *this << endl;
			if (turn() == quit)
			{
				cout << "You have quit the game. " << moves << " moves were played." << endl;
				return quit;
			}
			if (done() == true)
			{
				cout << *this << endl;
				cout << "Player " << winner << " won after " << moves << " moves" << endl;
				return success;
			}
			if (draw() == true)
			{
				cout << *this << endl;
				cout << "You drew." << endl;
				return tie;
			}
		}
		//Computer moves.
		while (XorO == "X")
		{
			if (moves > 0)
			{
				//The following loops check if there are 2 pieces in a row and places a piece to win.
				for (int i = 0; i < 3; ++i)
				{
					//Checking for vertical placement (relative to 1st row):
					if (board[6 + i] == "X")
					{
						if (board[6 + i] == board[11 + i])
						{
							if (board[16 + i] == " ")
							{
								board[16 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
						if (board[6 + i] == board[16 + i])
						{
							if (board[11 + i] == " ")
							{
								board[11 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
					//Checking for vertical placement (relative to 2nd and 3rd row):
					if (board[11 + i] == "X")
					{
						if (board[11 + i] == board[16 + i])
						{
							if (board[6 + i] == " ")
							{
								board[6 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
				}
				for (int i = 0; i < 11; i = i + 5)
				{
					//Checking for horizontal placement (realative to 1st column):
					if (board[6 + i] == "X")
					{
						if (board[6 + i] == board[7 + i])
						{
							if (board[8 + i] == " ")
							{
								board[8 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
						if (board[6 + i] == board[8 + i])
						{
							if (board[7 + i] == " ")
							{
								board[7 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
					//Checking for horizontal placement (realative to 2nd and 3rd column):
					if (board[7 + i] == "X")
					{
						if (board[7 + i] == board[8 + i])
						{
							if (board[6 + i] == " ")
							{
								board[6 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
				}
				//Checking for diagonal placement from center piece.
				if (board[12] == "X")
				{
					//x=y diagonal
					if (board[12] == board[6])
					{
						if (board[18] == " ")
						{
							board[18] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
					if (board[12] == board[18])
					{
						if (board[6] == " ")
						{
							board[6] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
					//x=-y diagonal
					if (board[12] == board[16])
					{
						if (board[8] == " ")
						{
							board[8] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
					if (board[12] == board[8])
					{
						if (board[16] == " ")
						{
							board[16] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
				}
				//Checking on line x=y
				if ((board[18] == "X") || (board[6] == "X"))
				{
					if (board[18] == board[6])
					{
						if (board[12] == " ")
						{
							board[12] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
				}
				//Checking on line x=-y
				if ((board[16] == "X") || (board[8] == "X"))
				{
					if (board[16] == board[8])
					{
						if (board[12] == " ")
						{
							board[12] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
				}

				//The following loops check if there are 2 pieces in a row and places a piece to block. (same as all loops
				//above, but checking for O instead of X.
				for (int i = 0; i < 3; ++i)
				{
					//Checking for vertical placement (relative to 1st row):
					if (board[6 + i] == "O")
					{
						if (board[6 + i] == board[11 + i])
						{
							if (board[16 + i] == " ")
							{
								board[16 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
						if (board[6 + i] == board[16 + i])
						{
							if (board[11 + i] == " ")
							{
								board[11 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
					//Checking for vertical placement (relative to 2nd and 3rd row):
					if (board[11 + i] == "O")
					{
						if (board[11 + i] == board[16 + i])
						{
							if (board[6 + i] == " ")
							{
								board[6 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
				}
				for (int i = 0; i < 11; i = i + 5)
				{
					//Checking for horizontal placement (realative to 1st column):
					if (board[6 + i] == "O")
					{
						if (board[6 + i] == board[7 + i])
						{
							if (board[8 + i] == " ")
							{
								board[8 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
						if (board[6 + i] == board[8 + i])
						{
							if (board[7 + i] == " ")
							{
								board[7 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
					//Checking for horizontal placement (realative to 2nd and 3rd column):
					if (board[7 + i] == "O")
					{
						if (board[7 + i] == board[8 + i])
						{
							if (board[6 + i] == " ")
							{
								board[6 + i] = "X";
								XorO = "O";
								++moves;
								goto label;
							}
						}
					}
				}
				//Checking for diagonal placement from center piece.
				if (board[12] == "O")
				{
					//x=y diagonal
					if (board[12] == board[6])
					{
						if (board[18] == " ")
						{
							board[18] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
					if (board[12] == board[18])
					{
						if (board[6] == " ")
						{
							board[6] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
					//x=-y diagonal
					if (board[12] == board[16])
					{
						if (board[8] == " ")
						{
							board[8] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
					if (board[12] == board[8])
					{
						if (board[16] == " ")
						{
							board[16] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
				}
				//Checking on line x=y
				if ((board[18] == "O") || (board[6] == "O"))
				{
					if (board[18] == board[6])
					{
						if (board[12] == " ")
						{
							board[12] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
				}
				//Checking on line x=-y
				if ((board[16] == "O") || (board[8] == "O"))
				{
					if (board[16] == board[8])
					{
						if (board[12] == " ")
						{
							board[12] = "X";
							XorO = "O";
							++moves;
							goto label;
						}
					}
				}
				//If there are no duplicates the best place to put a piece is a corner; since the initial move
				//the computer is to place it at 6, we want to check opposite corners to place.
				if (board[18] == " ")
				{
					board[18] = "X";
					++moves;
					XorO = "O";
					goto label;
				}
				if (board[16] == " ")
				{
					board[16] = "X";
					++moves;
					XorO = "O";
					goto label;
				}
				if (board[6] == " ")
				{
					board[6] = "X";
					++moves;
					XorO = "O";
					goto label;
				}
				if (board[8] == " ")
				{
					board[8] = "X";
					++moves;
					XorO = "O";
					goto label;
				}
				//Placing a piece if there are no duplicates and all corners are taken.
				int index;
				for (int i = 1; i < rows-1; ++i)
				{
					for (int x = 1; x < columns-1 ; ++x)
					{
						if (board[5 * x + i] == " ")
						{
							index = 5 * x + i;
						}
					}
				}
				board[index] = "X";
				++moves;
				XorO = "O";
			}
		}
		label:
		if (done() == true)
		{
			cout << *this << endl;
			cout << "Player " << winner << " won after " << moves << " moves" << endl;
			return success;
		}
		if (draw() == true)
		{
			cout << *this << endl;
			cout << "You drew." << endl;
			return tie;
		}
	}
	//Should never reach this point.
	return error;
}