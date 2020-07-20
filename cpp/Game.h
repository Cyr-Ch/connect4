#pragma once

#ifndef NONE
#define NONE 0x7FFFFFFF
#endif // NONE

using namespace std;

class Board;

class Game
{
public:
	const int rows = 6; // Height
	const int columns = 7; // Width
	int status = 0; // 0: running, 1: won, 2: lost, 3: tie
	int depth = 4; // Search depth
	int score = 100000; // Win / loss score
	int round = 1; // 0: Human, 1: Computer
	int iterations = 0; // Iteration count
	Board* board;

	Game();

	void place(int column);
	void generateComputerDecision();

	/* 
	Algorithm
    Minimax principle
	*/
	int* maximizePlay(Board game_board, int depth, int alpha = NONE, int beta = NONE);
	int* minimizePlay(Board game_board, int depth, int alpha = NONE, int beta = NONE);

	int8_t switchRound(int8_t round_switch);
	void updateStatus();
};