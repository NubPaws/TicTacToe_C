#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

char board[SIZE][SIZE];

// Prints the board in a pretty way
void printBoard() {
	int i, j;
	printf("  0 1 2\n");
	for (i = 0; i < SIZE; i++) {
		printf("%d|", i);
		for (j = 0; j < SIZE; j++)
			printf("%c|", board[i][j]);
		printf("\n");
	}
}

// This function resets the board to all ' ' (spaces)
void resetBoard() {
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			board[i][j] = ' ';
}

// Checks if a position is empty by comparing it to a space
int isEmpty(int x, int y) {
	return board[y][x] == ' ';
}

// Places a character at a position
void place(int x, int y, char c) {
	board[y][x] = c;
}

// Checks if a player won
int checkWin(char c) {
	int i;
	for (i = 0; i < SIZE; i++) {
		// Check row for victory
		if (board[i][0] == c && board[i][1] == c && board[i][2] == c)
			return 1;
		// Check col for victory
		if (board[0][i] == c && board[1][i] == c && board[2][i] == c)
			return 1;
	}
	// Check diagonal
	if (board[0][0] == c && board[1][1] == c && board[2][2] == c)
		return 1;
	if (board[0][2] == c && board[1][1] == c && board[2][0] == c)
		return 1;
	
	return 0;
}

// Check if the board is full, meaning there was no winner but a draw
int checkDraw() {
	int draw = 0;
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (board[i][j] != ' ')
				draw++;
	
	return draw >= (SIZE *SIZE);
}

int main() {
	resetBoard();
	
	int turn = 0;
	char currentPlayer;
	int x, y;
	int gameOver = 0;
	char playAgain = ' ';
	
	while (++turn) {
		printBoard();
		if (turn %2 == 1)
			currentPlayer = 'X';
		else currentPlayer = 'O';
		printf("Enter pos for %c [x, y]: ", currentPlayer);
		scanf("%d, %d", &x, &y);
		fflush(stdin);
		
		if (isEmpty(x, y)) {
			place(x, y, currentPlayer);
		} else {
			printf("Invalid move, try again!\n");
			currentPlayer--;
			continue;
		}
		
		if (checkWin(currentPlayer)) {
			printf("Player %c won\n", currentPlayer);
			gameOver = 1;
		}
		
		if (checkDraw()) {
			printf("Draw! Good luck next time.\n");
			gameOver = 1;
		}
		
		if (gameOver) {
			printf("Do you want to play again [y/n]: ");
			scanf("%c", &playAgain);
			if (playAgain == 'y') {
				resetBoard();
				gameOver = 0;
				turn = 0;
			} else if (playAgain == 'n')
				break;
		}
	}
	
	return 0;
}