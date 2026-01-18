/* These are standard libary files that i will be using in the game .
1. "iostream" used for basic i/o functions
2. "conio.h" used to read keyboard keys instantly
3. "windows.h" lets me use some windows functions like (clear screen)
4. "cstdlib" used to generate random numbers /candies
5. "iomanip" to format outut nicely
6. "fstream" used for file handling like write/read data from a file

*/
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <cstdlib>
#include<iomanip>
#include <fstream>
#include <chrono>

using namespace std;
/* Telling the computer to use W,S,A,D as arrow keys */

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100

/*Defined color for candies or characters */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*Below Two Functions are for timer*/

// Get time remaining in seconds
int get_remaining_time(chrono::steady_clock::time_point startTime, int timeLimit) {
	auto currentTime = chrono::steady_clock::now();
	int elapsed = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
	int timeLeft = timeLimit - elapsed;
	return (timeLeft > 0) ? timeLeft : 0;
}

// Display timer in MM:SS format
void display_timer(int timeLeft) {
	int minutes = timeLeft / 60;
	int seconds = timeLeft % 60;

	cout << "Time: ";
	if (minutes < 10) cout << "0";
	cout << minutes << ":";
	if (seconds < 10) cout << "0";
	cout << seconds;
}



/*Function to set candy colors and then update them */
void candy_colour(char ch) {
	switch (ch) {
	case '$':
		cout << ANSI_COLOR_RED;
		break;
	case '%':
		cout << ANSI_COLOR_GREEN;
		break;
	case '#':
		cout << ANSI_COLOR_YELLOW;
		break;
	case '&':
		cout << ANSI_COLOR_BLUE;
		break;
	case '*':
		cout << ANSI_COLOR_MAGENTA;
		break;
	case '!':
		cout << ANSI_COLOR_CYAN;
		break;
	case '@':
		cout << ANSI_COLOR_RED;
		break;
	default:
		cout << ANSI_COLOR_RESET;
	}
}

/* Function to generate a random candy based on difficulty For easy mode: pass 5, for hard mode: pass 7 */

char get_random_candy(int num_candies) {
	int randomNum = rand() % num_candies + 1;

	if (randomNum == 1) return '@';
	else if (randomNum == 2) return '#';
	else if (randomNum == 3) return '&';
	else if (randomNum == 4) return '$';
	else if (randomNum == 5) return '%';
	else if (randomNum == 6) return '!';
	else if (randomNum == 7) return '*';

	return '@';
}

/* Function to display easy board */

void display_easy_board(char board[8][8]) {
	cout << "\n";
	cout << "     ";
	for (int col = 0; col < 8; col++) {
		cout << " col" << col << " ";
	}
	cout << "\n";
	cout << "      ";
	for (int col = 0; col < 8; col++) {
		cout << "------";
	}
	cout << "\n";

	for (int row = 0; row < 8; row++) {
		cout << " row" << row << " |";

		for (int col = 0; col < 8; col++) {
			candy_colour(board[row][col]);   // Here i have used function within a function to change the colors
			cout << "  " << board[row][col] << ANSI_COLOR_RESET << "  |";
			//cout << "  " << board[row][col] << "  |";
		}
		cout << "\n";
		cout << "      ";
		for (int col = 0; col < 8; col++) {
			cout << "------";
		}
		cout << "\n";
	}
}

/* Function to display hard board */

void display_hard_board(char board[10][10]) {
	cout << "\n";
	cout << "     ";
	for (int col = 0; col < 10; col++) {
		cout << " col" << col << " ";
	}
	cout << "\n";
	cout << "      ";
	for (int col = 0; col < 10; col++) {
		cout << "------";
	}
	cout << "\n";

	for (int row = 0; row < 10; row++) {
		cout << " row" << row << " |";

		for (int col = 0; col < 10; col++) {
			candy_colour(board[row][col]); // Here i have used function within a function to change the colors
			cout << "  " << board[row][col] << ANSI_COLOR_RESET << "  |";
			//cout << "  " << board[row][col] << "  |";
		}
		cout << "\n";

		cout << "      ";
		for (int col = 0; col < 10; col++) {
			cout << "------";
		}
		cout << "\n";
	}
}

/* Function to get valid user input for candy selection */

void get_user_input(int& row, int& col, int boardSize) {
	cin.clear();
	cin.ignore(1000, '\n');

	while (true) {
		cout << "\n=== SELECT A CANDY ===" << endl;
		cout << "Enter row (0-" << boardSize - 1 << "): ";
		cin >> row;
		cout << "Enter column (0-" << boardSize - 1 << "): ";
		cin >> col;

		if (cin.fail()) {

			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input! Please enter numbers only." << endl;
			continue;
		}

		if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
			cout << "You selected: row " << row << ", col " << col << endl;
			break;
		}
		else {
			cout << "Invalid position! Row and column must be between 0 and "
				<< boardSize - 1 << endl;
		}
	}
}

/* Function to get direction from user using key codes */

int get_direction() {
	cout << "\n=== CHOOSE DIRECTION ===" << endl;
	cout << "Press: W (Up) | S (Down) | A (Left) | D (Right)" << endl;
	cout << "Your choice: ";

	int key = _getch();
	cout << (char)key << endl;


	if (key == KEY_UP || key == 87 ||
		key == KEY_DOWN || key == 83 ||
		key == KEY_LEFT || key == 65 ||
		key == KEY_RIGHT || key == 68) {
		return key;
	}
	else {
		cout << "Invalid key! Please use W, A, S, or D." << endl;
		return get_direction();
	}
}

/*Below are the function for easy mode (8*8)*/

int checkHorizontalMatchEasy(char board[8][8], int row, int col, int& matchLength) {
	char candy = board[row][col];
	if (candy == ' ') return 0;

	int count = 1;

	for (int c = col + 1; c < 8 && board[row][c] == candy; c++) count++;
	for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) count++;

	matchLength = count;
	return (count >= 3) ? count : 0;
}

int checkVerticalMatchEasy(char board[8][8], int row, int col, int& matchLength) {
	char candy = board[row][col];
	if (candy == ' ') return 0;

	int count = 1;

	for (int r = row + 1; r < 8 && board[r][col] == candy; r++) count++;
	for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) count++;

	matchLength = count;
	return (count >= 3) ? count : 0;
}

void removeHorizontalMatchEasy(char board[8][8], int row, int col) {
	char candy = board[row][col];
	if (candy == ' ') return;

	board[row][col] = ' ';

	for (int c = col + 1; c < 8 && board[row][c] == candy; c++) board[row][c] = ' ';
	for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) board[row][c] = ' ';
}

void removeVerticalMatchEasy(char board[8][8], int row, int col) {
	char candy = board[row][col];
	if (candy == ' ') return;

	board[row][col] = ' ';

	for (int r = row + 1; r < 8 && board[r][col] == candy; r++) board[r][col] = ' ';
	for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) board[r][col] = ' ';
}

void applyGravityEasy(char board[8][8], int numCandies) {
	for (int col = 0; col < 8; col++) {

		int writeRow = 7;

		for (int row = 7; row >= 0; row--) {
			if (board[row][col] != ' ') {
				board[writeRow][col] = board[row][col];
				writeRow--;
			}
		}

		while (writeRow >= 0) {
			board[writeRow][col] = get_random_candy(numCandies);
			writeRow--;
		}
	}
}

int detectAndProcessMatchesEasy(char board[8][8], int numCandies, int& totalGameScore) {
	int roundScore = 0; // Score for this particular swap

	while (true) {
		bool foundMatch = false;
		bool toRemove[8][8] = { false };

		// Step 1: detect and mark all matches
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (board[row][col] == ' ') continue;

				char candy = board[row][col];
				int hLen = 1, vLen = 1;

				// Horizontal check
				for (int c = col + 1; c < 8 && board[row][c] == candy; c++) hLen++;
				for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) hLen++;

				// Vertical check
				for (int r = row + 1; r < 8 && board[r][col] == candy; r++) vLen++;
				for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) vLen++;

				// Mark candies if they form a match
				if (hLen >= 3) {
					foundMatch = true;
					for (int c = col; c < 8 && board[row][c] == candy; c++) toRemove[row][c] = true;
					for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) toRemove[row][c] = true;
				}

				if (vLen >= 3) {
					foundMatch = true;
					for (int r = row; r < 8 && board[r][col] == candy; r++) toRemove[r][col] = true;
					for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) toRemove[r][col] = true;
				}
			}
		}

		if (!foundMatch) break;

		// Step 2: Calculate score for THIS match and display it
		int matchScore = 0;
		int matchCount = 0;

		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (toRemove[row][col] && board[row][col] != ' ') {
					matchCount++;
					board[row][col] = ' '; // Remove candy
				}
			}
		}

		// Determine score based on match count
		if (matchCount == 3) {
			matchScore = 10;
			cout << "   >>> 3-Match! +10 points" << endl;
		}
		else if (matchCount == 4) {
			matchScore = 15;
			cout << "   >>> 4-Match! +15 points" << endl;
		}
		else if (matchCount >= 5) {
			matchScore = 20;
			cout << "   >>> 5+ Match! +20 points" << endl;
		}

		roundScore += matchScore;
		totalGameScore += matchScore;

		// Step 3: Apply gravity
		applyGravityEasy(board, numCandies);

		// Show board after each cascade if there are more matches
		if (foundMatch) {
			Sleep(500); // Brief pause to show cascade effect
		}
	}

	return roundScore;
}

bool swap_candy_easy(char board[8][8], int row, int col, int direction) {
	int newRow = row;
	int newCol = col;

	// Calculate new position based on direction
	switch (direction) {
	case KEY_UP:    // w
	case 87:        // W
		newRow = row - 1;
		cout << "Swapping UP..." << endl;
		break;
	case KEY_DOWN:  // s
	case 83:        // S
		newRow = row + 1;
		cout << "Swapping DOWN..." << endl;
		break;
	case KEY_LEFT:  // a
	case 65:        // A
		newCol = col - 1;
		cout << "Swapping LEFT..." << endl;
		break;
	case KEY_RIGHT: // d
	case 68:        // D
		newCol = col + 1;
		cout << "Swapping RIGHT..." << endl;
		break;
	}
	// Check if new position is valid
	if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
		// Perform the swap
		char temp = board[row][col];
		board[row][col] = board[newRow][newCol];
		board[newRow][newCol] = temp;

		cout << "Swap successful!" << endl;
		return true;
	}
	else {
		cout << "Cannot swap - out of bounds!" << endl;
		return false;
	}
}



/*Below are the function for hard mode (10*10)*/

int checkHorizontalMatchHard(char board[10][10], int row, int col, int& matchLength) {
	char candy = board[row][col];
	if (candy == ' ') return 0;

	int count = 1;

	for (int c = col + 1; c < 10 && board[row][c] == candy; c++) count++;
	for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) count++;

	matchLength = count;
	return (count >= 3) ? count : 0;
}

int checkVerticalMatchHard(char board[10][10], int row, int col, int& matchLength) {
	char candy = board[row][col];
	if (candy == ' ') return 0;

	int count = 1;

	for (int r = row + 1; r < 10 && board[r][col] == candy; r++) count++;
	for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) count++;

	matchLength = count;
	return (count >= 3) ? count : 0;
}

void removeHorizontalMatchHard(char board[10][10], int row, int col) {
	char candy = board[row][col];
	if (candy == ' ') return;

	board[row][col] = ' ';

	for (int c = col + 1; c < 10 && board[row][c] == candy; c++) board[row][c] = ' ';
	for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) board[row][c] = ' ';
}

void removeVerticalMatchHard(char board[10][10], int row, int col) {
	char candy = board[row][col];
	if (candy == ' ') return;

	board[row][col] = ' ';

	for (int r = row + 1; r < 10 && board[r][col] == candy; r++) board[r][col] = ' ';
	for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) board[r][col] = ' ';
}

void applyGravityHard(char board[10][10], int numCandies) {
	for (int col = 0; col < 10; col++) {

		int writeRow = 9;

		for (int row = 9; row >= 0; row--) {
			if (board[row][col] != ' ') {
				board[writeRow][col] = board[row][col];
				writeRow--;
			}
		}

		while (writeRow >= 0) {
			board[writeRow][col] = get_random_candy(numCandies);
			writeRow--;
		}
	}
}

int detectAndProcessMatchesHard(char board[10][10], int numCandies, int& totalGameScore) {
	int roundScore = 0;

	while (true) {
		bool foundMatch = false;
		bool toRemove[10][10] = { false };

		// Step 1: detect matches and mark them
		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 10; col++) {
				if (board[row][col] == ' ') continue;

				char candy = board[row][col];
				int hLen = 1, vLen = 1;

				// Horizontal check
				for (int c = col + 1; c < 10 && board[row][c] == candy; c++) hLen++;
				for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) hLen++;

				// Vertical check
				for (int r = row + 1; r < 10 && board[r][col] == candy; r++) vLen++;
				for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) vLen++;

				// Mark candies to remove
				if (hLen >= 3) {
					foundMatch = true;
					for (int c = col; c < 10 && board[row][c] == candy; c++) toRemove[row][c] = true;
					for (int c = col - 1; c >= 0 && board[row][c] == candy; c--) toRemove[row][c] = true;
				}

				if (vLen >= 3) {
					foundMatch = true;
					for (int r = row; r < 10 && board[r][col] == candy; r++) toRemove[r][col] = true;
					for (int r = row - 1; r >= 0 && board[r][col] == candy; r--) toRemove[r][col] = true;
				}
			}
		}

		if (!foundMatch) break;

		// Step 2: calculate score and show individual match
		int matchScore = 0;
		int matchCount = 0;

		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 10; col++) {
				if (toRemove[row][col] && board[row][col] != ' ') {
					matchCount++;
					board[row][col] = ' '; // Remove candy
				}
			}
		}

		// Determine score based on match count
		if (matchCount == 3) {
			matchScore = 10;
			cout << "   >>> 3-Match! +10 points" << endl;
		}
		else if (matchCount == 4) {
			matchScore = 15;
			cout << "   >>> 4-Match! +15 points" << endl;
		}
		else if (matchCount >= 5) {
			matchScore = 20;
			cout << "   >>> 5+ Match! +20 points" << endl;
		}

		roundScore += matchScore;
		totalGameScore += matchScore;

		// Step 3: apply gravity
		applyGravityHard(board, numCandies);

		if (foundMatch) {
			Sleep(500); // Brief pause for cascade effect
		}
	}

	return roundScore;
}


bool swap_candy_hard(char board[10][10], int row, int col, int direction) {
	int newRow = row;
	int newCol = col;

	// Calculate new position based on direction
	switch (direction) {
	case KEY_UP:
	case 87:
		newRow = row - 1;
		cout << "Swapping UP..." << endl;
		break;
	case KEY_DOWN:
	case 83:
		newRow = row + 1;
		cout << "Swapping DOWN..." << endl;
		break;
	case KEY_LEFT:
	case 65:
		newCol = col - 1;
		cout << "Swapping LEFT..." << endl;
		break;
	case KEY_RIGHT:
	case 68:
		newCol = col + 1;
		cout << "Swapping RIGHT..." << endl;
		break;
	}

	// Check if new position is valid
	if (newRow >= 0 && newRow < 10 && newCol >= 0 && newCol < 10) {
		// Perform the swap
		char temp = board[row][col];
		board[row][col] = board[newRow][newCol];
		board[newRow][newCol] = temp;

		cout << "Swap successful!" << endl;
		return true;
	}
	else {
		cout << "Cannot swap - out of bounds!" << endl;
		return false;
	}
}

int easyTotalScore = 0;  // persists across multiple plays of Easy Mode
int hardTotalScore = 0;  // persists across multiple plays of Hard Mode

int main() {
	/* This section of code is for menu .This loop keeps the menu running until user chooses to exit */

	srand(time(0));
	while (true) {

		cout << "\n";
		cout << " ========================================" << endl;
		cout << "|                                        |" << endl;
		cout << "|        CANDY CRUSH GAME MENU           |" << endl;
		cout << "|                                        |" << endl;
		cout << " ========================================" << endl;
		cout << "|                                        |" << endl;
		cout << "|  1. EASY MODE                          |" << endl;
		cout << "|     (8x8 board, 60 seconds)            |" << endl;
		cout << "|                                        |" << endl;
		cout << "|  2. HARD MODE                          |" << endl;
		cout << "|     (10x10 board, 40 seconds)          |" << endl;
		cout << "|                                        |" << endl;
		cout << "|  3. VIEW SCORES                        |" << endl;
		cout << "|                                        |" << endl;
		cout << "|  4. EXIT                               |" << endl;
		cout << "|                                        |" << endl;
		cout << " ========================================" << endl;
		cout << "\n  Enter your choice (1-4): ";

		int choice;
		cin >> choice;

		/*The "system("cls")" clear the screen every time for better display */

		system("cls");


		if (choice == 1) {
			cout << "\n Starting Easy Mode..." << endl;
			cout << " Board: 8x8" << endl;
			cout << " Time: 60 seconds" << endl;
			cout << " Candies: @ # & $ %" << endl;

			char easyBoard[8][8];
			for (int row = 0; row < 8; row++)
				for (int col = 0; col < 8; col++)
					easyBoard[row][col] = get_random_candy(5);

			int timeLimit = 60;
			auto startTime = chrono::steady_clock::now();

			while (true) {
				int timeLeft = get_remaining_time(startTime, timeLimit);
				if (timeLeft <= 0) {
					system("cls");
					cout << "\n==============================" << endl;
					cout << "        TIME'S UP!" << endl;
					cout << "==============================" << endl;
					cout << " Final Score: " << easyTotalScore << endl;
					cout << "==============================" << endl;
					break;
				}

				cout << "\n========================================" << endl;
				display_timer(timeLeft);
				cout << "        Score: " << easyTotalScore << endl;  
				cout << "========================================" << endl;

				display_easy_board(easyBoard);

				int selectedRow, selectedCol;
				get_user_input(selectedRow, selectedCol, 8);

				int direction = get_direction();
				if (!swap_candy_easy(easyBoard, selectedRow, selectedCol, direction)) {
					cout << "Swap failed! Try again." << endl;
					continue;
				}

				// Process matches and update score
				int score = detectAndProcessMatchesEasy(easyBoard, 5, easyTotalScore);

				if (score > 0) {
					cout << "\n Total points this turn: " << score << endl;
					cout << " Current game score: " << easyTotalScore << endl;
				}
				else {
					cout << "No match. Swap didn't create a valid combination." << endl;
				}

				cout << "\nPress Enter to continue...";
				cin.ignore();
				cin.get();
				system("cls");
			}
		}


		else if (choice == 2) {
			cout << "\n Starting Hard Mode..." << endl;
			cout << " Board: 10x10" << endl;
			cout << " Time: 40 seconds" << endl;
			cout << " Candies: @ # & $ % ! *" << endl;

			char hardBoard[10][10];
			for (int row = 0; row < 10; row++) {
				for (int col = 0; col < 10; col++) {
					hardBoard[row][col] = get_random_candy(7);
				}
			}

			int timeLimit = 40;
			auto startTime = chrono::steady_clock::now();

			while (true) {
				int timeLeft = get_remaining_time(startTime, timeLimit);

				if (timeLeft <= 0) {
					system("cls");
					cout << "\n==============================" << endl;
					cout << "        TIME'S UP!" << endl;
					cout << "==============================" << endl;
					cout << " Final Score: " << hardTotalScore << endl;
					cout << "==============================" << endl;
					break;
				}

				cout << "\n========================================" << endl;
				display_timer(timeLeft);
				cout << "        Score: " << hardTotalScore << endl;  
				cout << "========================================" << endl;

				display_hard_board(hardBoard);

				int selectedRow, selectedCol;
				get_user_input(selectedRow, selectedCol, 10);

				int direction = get_direction();
				if (!swap_candy_hard(hardBoard, selectedRow, selectedCol, direction)) {
					cout << "Swap failed! Try again." << endl;
					continue;
				}

				// Process matches and calculate score 
				int score = detectAndProcessMatchesHard(hardBoard, 7, hardTotalScore);

				if (score > 0) {
					cout << "\n Total points this turn: " << score << endl;
					cout << " Current game score: " << hardTotalScore << endl;
				}
				else {
					cout << "No match. Swap didn't create a valid combination." << endl;
				}

				cout << "\nPress Enter to continue...";
				cin.ignore();
				cin.get();
				system("cls");
			}
		}

		else if (choice == 3) {
			cout << "\n ============================================" << endl;
			cout << "              HIGH SCORES" << endl;
			cout << " ============================================" << endl;
			cout << "\n EASY MODE:" << endl;
			cout << "Total score : " << easyTotalScore << endl;
			cout << "\n HARD MODE:" << endl;
			cout << "Total score : " << hardTotalScore << endl;
			cout << " ============================================" << endl;
			cout << "\n Press any key to return to menu...";
			cin.ignore();
			cin.get();
			system("cls");
		}
		else if (choice == 4) {
			// EXIT option
			cout << "\n ========================================" << endl;
			cout << "   Thanks for playing Candy Crush!" << endl;
			cout << " ========================================" << endl;
			break;
		}
		else {
			// Invalid operation
			cout << "\n Invalid choice!" << endl;
			cin.ignore();
			cin.get();
			system("cls");
		}
	}




	return 0;
}