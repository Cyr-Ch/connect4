#pragma once

using namespace std;

/* @constructor
 @this {Board}
 @param {Game} game The main-game object.
 @param {array} field The field containing our situation.
 @param {number} player The current player.
*/

class Game;

class Board
{
public:
	Board( void );
	Board(Game* game_arg, vector<vector<int8_t>> field_arg, int8_t player_arg);
	~Board();

	Game* game;
	vector<vector<int8_t>> field;
	int8_t player;

	/* Determines if situation is finished.
	@param {number} depth
	@param {number} score
	@return {boolean} */
	bool isFinished(int depth, int score);

	/* Place in current board.
	@param {number} column
	@return {boolean} */
	bool place(int column);

	/* Return a score for various positions (either horizontal, vertical or diagonal by moving through our board).
	@param {number} row
	@param {number} column
	@param {number} delta_y
	@param {number} delta_x
	@return {number} */
	int scorePosition(int row, int column, int delta_y, int delta_x);

	/* Returns the overall score for our board.
	@return {number} */
	int score();

	/* Determines if board is full.
    @return {boolean} */
	bool isFull();

	/* Returns a copy of our board.
	@return {Board}*/
	Board copy();
};
