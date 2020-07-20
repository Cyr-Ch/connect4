#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Game.h"

Board::Board( void ) {};

Board::Board(Game* game_arg, vector< vector<int8_t>> field_arg, int8_t player_arg) : game(game_arg), field(field_arg), player(player_arg) {};

Board::~Board() {};

bool Board::isFinished(int depth, int score) {
	if ((depth == 0) | (score == this->game->score) | (score == -(this->game->score)) | this->isFull())
	{ 
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::place(int column) {
	// Check if column valid
	// 1. not empty 2. not exceeding the board size
	if ((this->field[0][column] == 0) & (column >= 0) & (column < this->game->columns))
	{
		// Bottom to top
		for (int i = (this->game->rows - 1); i >= 0; i--)
		{
			if (this->field[i][column] == 0)
			{
				// Set current player coin
				this->field[i][column] = this->player;
				break;
				//# Break from loop after inserting
			}
		}
		this->player = this->game->switchRound(this->player);
		return true;
	}
	else
	{
		return false;
	}
}

int Board::scorePosition(int row, int column, int delta_y, int delta_x)
{
	int human_points = 0;
	int computer_points = 0;

	// Determine score through amount of available chips
	for (int i = 0; i < 4; i++)
	{
		if (this->field[row][column] == 1)
		{
			// Add for each human chip
			human_points++;
		}
		else if (this->field[row][column] == 2)
		{
			// Add for each computer chip
			computer_points++;
		}
		// Moving through our board
		row += delta_y;
		column += delta_x;
	}
	// Marking winning / returning score
	if (human_points == 4)
	{
		// Computer won(100000)
		return -(this->game->score);
	}
	else if (computer_points == 4)
	{
		// Human won (-100000)
		return (this->game->score);
	}
	else
	{
		// Return normal points
		return computer_points;
	}
}

int Board::score()
{

	int vertical_points = 0;
	int	horizontal_points = 0;
	int	diagonal_points1 = 0;
	int	diagonal_points2 = 0;

	// Board-size: 7x6 (height x width)
	// Array indices begin with 0
	// => e.g. height: 0, 1, 2, 3, 4, 5

	// Vertical points
	// Check each column for vertical score
	//
	// Possible situations
	//  0  1  2  3  4  5  6
	// [x][ ][ ][ ][ ][ ][ ] 0
	// [x][x][ ][ ][ ][ ][ ] 1
	// [x][x][x][ ][ ][ ][ ] 2
	// [x][x][x][ ][ ][ ][ ] 3
	// [ ][x][x][ ][ ][ ][ ] 4
	// [ ][ ][x][ ][ ][ ][ ] 5


	for (int row = 0; row < (this->game->rows - 3); row++)
	{
		//Für jede Column überprüfen
		for (int column = 0; column < (this->game->columns); column++)
		{
			// Die Column bewerten und zu den Punkten hinzufügen
			int score = this->scorePosition(row, column, 1, 0);
			if (score == this->game->score)
			{
				return this->game->score;
			}
			else if (score == -(this->game->score))
			{
				return -(this->game->score);
			}
			vertical_points += score;
		}
	}

	// Horizontal points
	// Check each row's score
	//
	// Possible situations
	//  0  1  2  3  4  5  6
	// [x][x][x][x][ ][ ][ ] 0
	// [ ][x][x][x][x][ ][ ] 1
	// [ ][ ][x][x][x][x][ ] 2
	// [ ][ ][ ][x][x][x][x] 3
	// [ ][ ][ ][ ][ ][ ][ ] 4
	// [ ][ ][ ][ ][ ][ ][ ] 5

	for (int row = 0; row < (this->game->rows); row++)
	{
		for (int column = 0; column < (this->game->columns - 3); column++)
		{
			int score = this->scorePosition(row, column, 0, 1);
			if (score == this->game->score)
			{
				return this->game->score;
			}
			else if (score == -(this->game->score))
			{
				return -(this->game->score);
			}
			horizontal_points += score;
		}
	}

	// Diagonal points 1 (left-bottom)
	//
	// Possible situation
	//  0  1  2  3  4  5  6
	// [x][ ][ ][ ][ ][ ][ ] 0
	// [ ][x][ ][ ][ ][ ][ ] 1
	// [ ][ ][x][ ][ ][ ][ ] 2
	// [ ][ ][ ][x][ ][ ][ ] 3
	// [ ][ ][ ][ ][ ][ ][ ] 4
	// [ ][ ][ ][ ][ ][ ][ ] 5

	for (int row = 0; row < (this->game->rows - 3); row++)
	{
		for (int column = 0; column < (this->game->columns - 3); column++)
		{
			int score = this->scorePosition(row, column, 1, 1);
			if (score == this->game->score)
			{
				return this->game->score;
			}
			else if (score == -(this->game->score))
			{
				return -(this->game->score);
			}
			diagonal_points1 += score;
		}
	}

	// Diagonal points 2 (right-bottom)
	//
	// Possible situation
	//  0  1  2  3  4  5  6
	// [ ][ ][ ][x][ ][ ][ ] 0
	// [ ][ ][x][ ][ ][ ][ ] 1
	// [ ][x][ ][ ][ ][ ][ ] 2
	// [x][ ][ ][ ][ ][ ][ ] 3
	// [ ][ ][ ][ ][ ][ ][ ] 4
	// [ ][ ][ ][ ][ ][ ][ ] 5

	for (int row = 3; row < (this->game->rows); row++)
	{
		for (int column = 0; column < (this->game->columns - 3); column++)
		{
			int score = this->scorePosition(row, column, -1, 1);
			if (score == this->game->score)
			{
				return this->game->score;
			}
			else if (score == -(this->game->score))
			{
				return -(this->game->score);
			}
			diagonal_points2 += score;
		}
	}

	int points = horizontal_points + vertical_points + diagonal_points1 + diagonal_points2;
	return points;
}

bool Board::isFull()
{
	for (int i = 0; i < this->game->columns; i++)
	{
		if (this->field[0][i] == 0)
		{
			return false;
		}
	}
	return true;
};

Board Board::copy()
{
	Board* board = new Board(*this);
	return *board;
};
