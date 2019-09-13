The following explains the object oriented behaviour, structure, and tests performed for a TicTacToe game which can be played between 2 players or against a (smart) computer.

I initialy created a header which would hold the class (TicTacToeGame) and any enums or return values for my 
functions. 
When creating the TicTacToeGame I gave it 3 private (by default) member variables: row and column, which I 
initially assigned to 5, and board, which was a vector of strings to represent the board with X's and O's.
I then proceeded to create the constructor for my TicTacToeGame, which would simply fill the vector with 25
entries of nothing (""). I tested that inspite of filling the vector with "" (which is considered empty when
calling string::empty returns true) by testing the following in my main:
vector<string> test;
	for (int i = 0; i < 25; ++i)
	{
		test.push_back("");
	}
	cout << test.size() << endl;
25 was outputed to the terminal, which means that even though it is filled with empty strings, the indices of the
vector were created. To initialize the board to have a size of 25 in my constructor I simply ran 2 loops, one running
from 0 to rows-1 and a nested loop running from 0 to columns-1 and just pushed back "". At this point all my 
member variables (row, column, and board) were initialized.

I then started building the methods of the class (which are all public). I began by building the << operator 
method, by making it a friend method (so it could have access to all the private member variables and of the 
class). The output stream printed out the board from top to bottom and from left to right, every time it started
a new row (whenever column was 0) it printed out the row and after printing out the entire board I printed out
the rows at the bottom. To test that it worked properly I filled the board with x's in the constructor and printed
out a TicTacToeGame object in the main. The following output was produced:
4xxxxx
3xxxxx
2xxxxx
1xxxxx
0xxxxx
 01234
 Which is the behaviour I was looking for.

 I then began instantiating the done() function but realized it would be easier once I figured out how pieces
 and squares were represente. I then began instantiating the draw function; I declared it in the class, and 
 defined it in the main. Here I realized that I would probably need a "moves" variable to hold the number of 
 moves of a current game. I created a member variable "moves" in the class and left it undefined. For draw() I
 only said that if done()==true or moves<9 then it returned false, else it returned true. This is because if there
 is a winner this will make done() return true, and if there is no winner all 9 squares would be finished. 

 At this point I went back to test my board formation and printed out an X at index 7, which should be, by
 my indexing function, located at row 1 column 2, but the printout was the following:
4
3
2
1X
0
 01234
Which printed out the x in the 1st row but 0th column, which meant that the "" which with I filled the board
were not going to work. So I went back to my constructor and filled the board with spaces, " ". I added some lines
to the board so that it would look better when printing and got the following ouptput when pushing back an X
to the board at index 7 (1st row, 2nd column):
4 | | | | |
 ----------
3 | | | | |
 ----------
2 | | | | |
 ----------
1 | |X| | |
 ----------
0 | | | | |
 ----------
 0 1 2 3 4

I began building the prompt() method. To do this I prompted the user for a valid coordinate (written as 
row,column) or for the word quit to quit and exit the game. I read in the users input into a string variable
and I first checked if the first character of the string was an alphabetical character using the isalpha function.
If it was I then made the string all lower case (using the function lowerCaseStings, created in lab 2) and checked
if the string was equal to quit. If it was it printed out "You have quit the game" and returned a non 0 value
representing quit, otherwise it asked the user to provide correct input and called the function recursively. 
I tested it by giving it variants of quit (e.g. Quit, QUIT, etc.) and every time it printed out "You have
quit the game", and the error level returned by echo %errorlevel% was 2. When giving it words that did not make
any sense the following was prompted:
Please provide a VALID input.
Provide a position to place your piece in the following format:
row,column. Where row and column have to be greater than or equal to 1 and less than or equal to 3.
Or enter quit if you wish to quit the game.
Now, if the first character wasn't alphabetic I checked to see if the length of the string that was read in
was exacly 3 (row comma column),and I checked to see that the first and third index [0] and [2] of the string 
were digits (using isdigit()), and the second index [1] was a comma: ','. If this stood I replaced the comma
with whitespace, ' ', and wrapped the string into an istringstream and then pushed the values to row and column
(the parameters taken in by the method). I then checked if row and column were between 1 and 3 inclusive,
if they were I returned success, otherwise I reprompted the user recursively for valid input.

Then I began building the turn() method, and to do so I created a member variable XorO in the class which 
was initialized to "X" (but can be changed to the player you wish to begin (X or O)). I then, in 2 for loops
(depending on weather XorO was X or O) I did essentially the same thing which was to call prompt(); if prompt
== quit, then turn() would return quit. Otherwise I would create the index by multiplying columns (member variable)
by row and adding columns (which were extracted from the call to prompt()). I then checked if the board at that 
index had something other than a whitespace, " ", if it did the message: "There is already a piece at the given 
location, please try again" would be printed out and turn() would be called recursively; if the board at that 
index had whitespace I would place the X or O, increment the member variable, moves by 1, and then change the 
value of XorO to the other player and return success.

For the play() method I simply made a while loop which ran as long as moves was less than 9 and in that loop
I printed out *this, and then saw if turn() == quit, if so I returned quit with the printout "You have quit the
game after (moves) moves" , if done() == true, if so I returned success, and if draw() == true I would return 
tie along with the printout message: You drew.

I then went back and instantiated my done() method. The way I did this was by checking all the rows in one for 
loop, with increments of 5(because for example indices 6,7,8 corresponded to (1,1), (1,2), and (1,3) respectively
and indices 11, 12, 13 corresponded to (2,1), (2,2), (2,3) respectively) and all the columns in one for loop with
increments of one (because for example indices 6, 11, 16 corresponded to (1,1), (2,1), (3,1) respectively). And I
checked both diagonals in a separate for loop which simply compared values. To compare values I just made sure that
they were equal, and I created a member variable for the class called winner wich I did not initialized,
and I simply initialized it in these for loops and added this variable to the printout message of play() when
it calls done() == true.

I then set up my main, by checking if argc was equal to the number of expected command line arguments (2) and
checking if the command line argument provided by the user equaled TicTacToe (by saving argv[1] in a string). 
If both these conditions were met I created a new TicTacToeGame and returned the object .play() (which would 
provide the same return provided by calling play on that object). If either of the requirements were not met 
then I would return a ussage message which read: Incorrect number or format of command line arguments, 
expected 1 command line argument in the format: TicTacToe.

Testing and checking for errors:
The first error I noticed was that when playing and giving nonsense as the first move and then trying to quit
I got a vector out of subscript range, and I fixed this by not only recursively calling prompt whenever the 
input was invalid but by returning a call to prompt. I did the same thing for turn() where if there was already
a piece at a given square I not only called turn() recursively but returned that call. I then performed the following
tests:
Giving the wrong number or format of command line arguments, after multiple tests and formats they all returned
the ussage message and the error level was 4, which is wrongCmdLineArgs.
When actually running the game whenever I gave it non-valid input it would always reprompt the user and when
trying to place a piece in a square that was already filled it would also reprompt with the appropriate message.
Whenever quit was called the error level given was 2, which represents quit. 
When someone won the correct message "Congratulations, player ____ won after ___ moves" printed out with the correct
winner and number of moves and the return level was 0, which represents success.
If the match ended in a draw, the correct outuput message: "You drew" with the correct error level: 3, which 
represents tie.
After going back and looking at my code I noticed that the turn() method was very repetitive, as I literally
copied the scenarios for X and O and it looked as follows:
if (XorO == "X")
	{
		//cout << "Player " << XorO << ": " << endl;
		cout << "Player X: " << endl;
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
				board[index] = "X";
				++moves;
				XorO = "O";
				return success;
			}
		}
	}
	else
	{
		cout << "Player O: " << endl;
		if (prompt(ro, co) == quit)
		{
			return quit;
		}
		else
		{
			int index = columns*ro + co;
			if (board[index] != " ")
			{
				cout << " " << endl;
				cout << "There is already a piece at the given location, please try again." << endl;
				return turn();
			}
			else
			{
				board[index] = "O";
				++moves;
				XorO = "X";
				return success;
			}
		}
	}
So I changed it so it would output XorO and simply check if XorO was X and change it. I also added the option
for the user to choose weather X or O would start, this is done in the turn() metod but only occurs when moves
is equal to 0.

After a few more tests and debugging I noticed that the stack looked messy when calling functions recursively
to ask for an appropriate input, so instead of recursion I just wrapped prompt() and turn() in a while loop.

Computer player:
I began by giving the player the option to start (O) or for the computer to start (X). I encompassed all playing
moves, weather they were computer or user moves in a while loop which ran up to moves<9. If the computer started I 
placed the piece in the bottom left corner (because there technically is no best place to put your first piece
but generally it is preferred to place in a corner), but otherwise I called turn() for the user to play. But since in my turn
function I have the option for the player to choose weather X or O may start, I initialized the value of XorO in
my class to be "empty", so that turn() would only prompt the user for X or O to start if moves == 0 and 
XorO == empty. For the player moves I essentially copied the play() method which calls turn draw and done
and sees if they have a specific return (quit, true, and true respectively) and if so it returns those values.
For moves other than the first move for the computer I first check if there are any 2 adjacent pieces 
(with for loops similar to those used in the done() method to check if there are 3 in a row); if there
are I check if the next adjacent square is empty, if so I place X there, change XorO to O, add one to moves and
jump to the end of the functions which keep checking this. If there are no adjacent pieces I create an index
by creating a double nested loop from 1 to rows-1 and 1 to columns-1 and checking if the index there is an empty
space; if it is I set a variable to this value and place an X there, increase the number of moves and change
XorO to O. I then changed my main to see if only 1 command line was inputed, or if 2 were provided I checked
for the 2nd cmdlinearg to be auto_play which would call game.auto_play().
The problem with my initial method is that it determined weather there was a place to block a winning move
or if there was a place to win, and the order for this depended on the order in which the code was written
(first checks for vertical combinations, then horizontal, and then diagonal); so say that there was an opportunity
for the computer to win if it placed a diagonal X, but the current state of the board had the user with 2 pieces
in a vertical combination, then it would first block the user instead of going directly for the win. 
Example of how I initially wrote this:
if (board[6 + i] == "X" || board[6 + i] == "O")
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
So what I did was check if there was an opportunity to win first and then check if there was an oportunity to block.
I simply copied and pasted all searches, but looking at X first and O after looking for all X possibilities.
Because I copy pasted all the option searches the code looks very long, but after multiple tests it works
perfectly; the computer first tries to look for a place to win and then blocks the user from winning if there
are 2 in a row.
I then noticed that when the computer started there was one way to beat it, which sould not be the case with
TicTacToe (whenever a player starts, the best case scenario for the other player should be to draw). So to avoid
this, after looking for winning or blocking moves the first thing the computer does is place a piece in a corner;
since the first corner the computer plays is the lower left corner, then it first looks to see if the upper right
corner is empty, else it looks at the other corners.

Additions to the main program: Going back and reading the lab instructions I noticed that I was missing the successful moves each
player performed printed out after the board (e.g Player O: 3, 2; 3, 3). To do so I simply initialized 2 variables
in my class: Xmoves and Ymoves which I initiated to "X: " and "Y: " respectively and I concetenated row and columnn
by calling (to_string) on these in the turn() method after someone inputs a valid move.
