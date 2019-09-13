/* Header for Lab 3.
Mauricio Fossas Koval
mauricio.fossas@wustl.edu
Contains all possible return values, expected number of arguments, declaration of TicTacToe class and prior
definition of some of the member variables of the class. 
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>

enum errors {
	success, notRead, quit, tie, wrongCmdLineArgs, error
};

enum expectedArgs {
	programName = 0, cmdLineArg = 1, numarguments = 2, numargsWExtraCredit = 3
};

std::string lowerCaseStings(std::string & word);
int usageMessage(char * program);

class TicTacToeGame {
	int rows=5;
	int columns=5;
	int moves=0;
	std::string Xmoves = "X: ";
	std::string Omoves = "O: ";
	std::string XorO = "empty";
	std::string winner;
	std::vector<std::string> board;
public:
	TicTacToeGame();
	friend std::ostream &operator<< (std::ostream &output, TicTacToeGame &game);
	bool done();
	bool draw();
	int prompt(unsigned int &row, unsigned int &col);
	int turn();
	int play();
	//Extra credit
	int autoplayer();
};