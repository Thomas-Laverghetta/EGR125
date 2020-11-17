#include "TicTacToe.h"

/* Creating a dummy data type*/
template <typename T>

/* Used for checking multple values in a if statement*/
bool ListMatcher(const T& val, const initializer_list<T>& list /* converts to a list (like an array)*/)
{
	// Seeing if one of the values in the list matches
	for (const auto& i : list) {
		if (val == i) {
			// return true if value matched
			return true;
		}
	}
	return false;
}

/* constructor for the initial moves*/
TicTacToe::TicTacToe()
{
	/* setting values equal to NULL*/
	for (int p = 0; p < Size; p++) {
		BoardMoves[p][0] = '\0';
		BoardMoves[p][1] = '\0';
		BoardMoves[p][2] = '\0';
	}
}

/* First player chance*/
int TicTacToe::First_Player()
{
	/* Inplanting the time seed*/
	srand(time(NULL));

	/* Each player gets a 50-50 chance at being first*/
	int Firstplayer = rand() % 2;

	// Displaying who's going first
	printf("\n%s is going first!\n\n", Player[Firstplayer].c_str());

	return Firstplayer;
}

/* Player enters their name*/
void TicTacToe::Enter_Player_Name(int N, bool AI)
{
	// Asking if the player is Computer
	if (!AI) {
		/* Prompt user to enter thier name*/
		printf("Enter Name for PLayer #%i: ", N + 1);
		getline(cin, Player[N]);
	}
	else if (AI) {
		// Stating that Player N is the computer
		Player[N] = "Computer";
	}

	// Defining each players Symbol
	Plays[Player[0]] = 'O';
	Plays[Player[1]] = 'X';

	// Displaying if the player is X or O
	cout << "\t" << Player[N] << " is " << Plays[Player[N]] << endl;

}

/* Display name*/
void TicTacToe::Display_Player_Name(int N)
{
	// displaying the Player's name
	cout << Player[N];
}

/* Prompt user to enter a move*/
void TicTacToe::Make_Move(int N)
{
	// Displaying the board
	Display_Board();

	// clearing the last cin
	cin.clear();

	// Letting the player enter a letter instead
	ABC['A'] = 0; ABC['a'] = 0; // 'A' and 'a' 
	ABC['B'] = 1; ABC['b'] = 1; // 'B' and 'b'
	ABC['C'] = 2; ABC['c'] = 2; // 'C' and 'c'

	// telling the user what computer's turn was in ABC
	ReverseABS[0] = 'A';
	ReverseABS[1] = 'B';
	ReverseABS[2] = 'C';

	/* Again is a goto statement*/
Again:
	if (Player[N] != "Computer") {
		/* Prompt player to make a move*/
		printf("%s Please make a move (RowCol Ex: A3): ", Player[N].c_str());
		cin >> CBA >> colMove;

		colMove--;
		rowMove = ABC[CBA];
		/* Testing the movement made*/
		bool V = Valid_Move();

		/* Test the results of V*/
		if (!V) { // If invalid move
			// Displaying Error
			cout << "Move invalid. Please Try a different Move: \a" << endl;
			
			// Clearing and ignoring the last cin
			cin.clear();
			cin.ignore();

			// goto Again statement
			goto Again;
		}
	}
	else {
		// Slow down computer
		Sleep(1000); // 1000 = 1000 ms or 1 sec

		// Get move for Computer
		AI_Moves(rowMove, colMove);

		// display move made by the computer
		printf("Computer's move: %c%i\n", ReverseABS[rowMove], colMove + 1);

		// slow down again
		Sleep(1000);
	}
	// Move is made
	BoardMoves[rowMove][colMove] = Plays[Player[N]];
}

/* validing moves made by player*/
int TicTacToe::Valid_Move()
{
	// if cin found a bad input 
	if (!cin) {
		return 0;
	}
	// Making sure the move made in the range
	else if (rowMove > 2 || rowMove < 0 || colMove > 2 || colMove < 0)
		return 0;
	// Checking to see if there was a move already made there
	else if (BoardMoves[rowMove][colMove] == '\0' && rowMove <= 2 && colMove <= 2) {
		return 1;
	}
	else
		return 0;
}

/* displaying the board*/
void TicTacToe::Display_Board()
{
	// declaring Alpha which displays A B C for board inputs
	char Alpha[] = { 'A','B','C' };
	cout << "\n";
	
	// Displaying the board with moves made
	printf("   1   2   3 \n");
	for (int k = 0; k < 3; k++) {
		cout << " " << string(14, '-') << endl;
		printf("%c| %c | %c | %c |\n", Alpha[k], BoardMoves[k][0], BoardMoves[k][1], BoardMoves[k][2]);
	}
	cout << " " << string(14, '-') << endl;
}

/* testing to see if the player won*/
int TicTacToe::Game_Over(int N)
{
	// Declaring Cat to equal 0
	int CAT = 0;

	// Looking for combinations for wins
	for (int i = 0; i < 3; i++) {
		// Accross horizontally
		if (BoardMoves[i][0] == Plays[Player[N]] && BoardMoves[i][1] == Plays[Player[N]] && BoardMoves[i][2] == Plays[Player[N]]) {
			return 1;
		}
		// Across Vertically
		else if (BoardMoves[0][i] == Plays[Player[N]] && BoardMoves[1][i] == Plays[Player[N]] && BoardMoves[2][i] == Plays[Player[N]]) {
			return 1;
		}
	}
	// first half of the digonal
	if (BoardMoves[0][0] == Plays[Player[N]] && BoardMoves[1][1] == Plays[Player[N]] && BoardMoves[2][2] == Plays[Player[N]]) {
		return 1;
	}
	// second Half of hte Digonal
	else if (BoardMoves[0][2] == Plays[Player[N]] && BoardMoves[1][1] == Plays[Player[N]] && BoardMoves[2][0] == Plays[Player[N]])
		return 1;

	/* Finding if the CAT won*/
	for (int row = 0; row < Size; row++)
	{
		for (int col = 0; col < Size; col++)
		{
			// if it finds a value either a X or O
			if (ListMatcher(BoardMoves[row][col], { 'X','O' }))
			{
				CAT++;
			}
		}
	}
	// if 9 out of the 9 spaces have values, and no-one has one
	// Then the CAT won
	if (CAT == 9)
		return 2;

	return 0;

}

void TicTacToe::AI_Moves(int & row, int & col)
{
	// initializing the time seed
	srand(time(NULL));

Rand:
	// rand number from 0 to 2
	row = rand() % 3;
	col = rand() % 3;
	// making sure that it doesn't use a value already defined
	if (BoardMoves[row][col] != '\0') {
		goto Rand; // not valid go to Rand Statement
	}

}

