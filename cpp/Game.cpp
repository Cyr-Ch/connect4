#pragma once
#include "stdafx.h"
#include "Game.h"
#include "Board.h"

Game::Game() 
{
	// Generate 'real' board
	// Create 2-dimensional array
	vector<vector<int8_t>> item (this->rows, std::vector<int8_t>(this->columns, 0));;
	// Create from board object (see board.js)
	this->board = new Board(this, item, 1);
};

void Game::place(int column) 
{
	// If not finished
	if ((this->board->score() != this->score) & (this->board->score() != -(this->score)) & (this->board->isFull() == false))
	{
		if (this->board->place(column) == false)
		{ printf("'Invalid Move'"); }
		this->round = this->switchRound(this->round);
		this->updateStatus();
	}
};

void Game::generateComputerDecision()
{
	if ((this->board->score() != this->score) & (this->board->score() != -(this->score)) & (this->board->isFull() == false))
	{
		this->iterations = 0;
		int* ai_move = this->maximizePlay(*(new Board(*(this->board))), depth);
		this->place(ai_move[0]);
	}
}

int* Game::maximizePlay(Board game_board, int depth, int alpha, int beta)
{
	// Call score of our board
	int score = game_board.score();

	// Break
	if (game_board.isFinished(depth, score))
	{
		return new int[2] { NONE, score };
	}

	// Column, Score
	int max_index[2] = { NONE, -99999 };

	// For all possible moves
	for (int column = 0; column < this->columns; column++)
	{
		// Create new board
		Board new_board = game_board.copy();
		Board* ptr_board = &new_board;
		if (new_board.place(column))
		{
			this->iterations++;

			// Recursive calling
			int* next_move = minimizePlay(new_board, (depth - 1), alpha, beta);
			// Evaluate new move
			if (max_index[0] == NONE | next_move[1] > max_index[1])
			{
				max_index[0] = column;
				max_index[1] = next_move[1];
				alpha = next_move[1];
			}

			if (alpha != NONE & beta != NONE)
			{
				if (alpha >= beta) 
				{
					return max_index;
				}
			}
		}
	}
	return max_index;
}

int* Game::minimizePlay(Board game_board, int depth, int alpha, int beta)
{
	int score = game_board.score();

	if (game_board.isFinished(depth, score))
	{
		return new int[2]{ NONE, score };
	}

	// Column, score
	int min_index[2] { NONE, 99999 };

	for (int column = 0; column < this->columns; column++)
	{
		Board new_board = game_board.copy();
		if (new_board.place(column))
		{
			this->iterations++;

			int* next_move = maximizePlay(new_board, (depth - 1), alpha, beta);
			int a = next_move[0];
			int b = next_move[1];
			if (min_index[0] == NONE | next_move[1] < min_index[1])
			{
				min_index[0] = column;
				min_index[1] = next_move[1];
				beta = next_move[1];
			}

			if (alpha != NONE & beta != NONE)
			{
				if (alpha >= beta)
				{
					return min_index;
				}
			}
		}
	}
	return min_index;
}

int8_t Game::switchRound(int8_t round_switch){
	// 0 Human, 1 Computer
	if (round_switch == 0)
		return 0;
	else
		return (round_switch == 1 ? 2 : 1);
};

void Game::updateStatus()
{
	if (this->board->score() == -(this->score))
	{
		this->status = 1;
		// Human won
	}
	if (this->board->score() == (this->score))
	{
		this->status = 2;
		// Computer won
	}
	if (this->board->isFull())
	{
		this->status = 3;
		// Tie
	}
}