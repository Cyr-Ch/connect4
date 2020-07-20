#include "stdafx.h"
#include "Game.h"
#include "Board.h"


void printBoard(vector<vector<int8_t>> board_field);

int main()
{
	Game game;
	game.place(3);
	printf("Test1");
	game.generateComputerDecision();
	printf("Test2");
	getchar();
	return 0;
}

void printBoard(vector<vector<int8_t>> board_field)
{
	for (int row = 0; row < 6; row++)
	{
		printf("%d: ", (row + 1));
		for (int column = 0; column < 7; column++)
		{
			if (board_field[row][column] == 0)
				printf(" ");
			else if (board_field[row][column] == 1)
				printf("o");
			else if (board_field[row][column] == 2)
				printf("x");
			else
				printf("Error on Row: %d and Column: %d \n", row, column);
		}
		printf("\n");
	}
	printf("   1234567");
}