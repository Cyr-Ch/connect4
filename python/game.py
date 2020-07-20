# Minimax (+Alpha-Beta) Implementation
# @plain javascript version

import board


class Game:
    def __init__(self):
        self.rows = 6
        # Height
        self.columns = 7
        # Width
        self.status = 0
        # 0: running, 1: won, 2: lost, 3: tie
        self.depth = 4
        # Search depth
        self.score = 100000
        # Win / loss score
        self.round = 0
        # 0: Human, 1: Computer
        self.winning_array = []
        # Winning(chips) array
        self.iterations = 0
        # Iteration count
        self.board = None
        self.initialize()

    def initialize(self):
        # Generate 'real' board
        # Create 2-dimensional array

        game_board = [None] * self.rows
        i = 0
        while i < len(game_board):
            game_board[i] = [None] * self.columns
            i += 1
        # Create from board object (see board.js)
        self.board = board.Board(self, game_board, 0)

    def place(self, column):
        # If not finished
        if (self.board.score() != self.score) & (self.board.score() != -self.score) & (self.board.is_full() is False):
            if self.board.place(column) is False:
                raise ValueError('Invalid Move')
            self.round = self.switch_round(self.round)
            self.update_status()

    def generate_computer_decision(self):
        if (self.board.score() != self.score) & (self.board.score() != -self.score) & (self.board.is_full() is False):
            self.iterations = 0
            ai_move = self.maximize_play(self.board, self.depth)
            self.place(ai_move[0])

    # Algorithm
    # Minimax principle
    def maximize_play(self, game_board, depth, alpha=None, beta=None):
        # Call score of our board
        score = game_board.score()

        # Break
        if game_board.is_finished(depth, score):
            return [None, score]

        # Column, Score
        max_index = [None, -99999]

        # For all possible moves
        column = 0
        while column < self.columns:
            # Create new board
            new_board = game_board.copy()
            if new_board.place(column):
                self.iterations += 1

                # Recursive calling
                next_move = self.minimize_play(new_board, (depth - 1), alpha, beta)

                # Evaluate new move
                if (max_index[0] is None) | (next_move[1] > max_index[1]):
                    max_index[0] = column
                    max_index[1] = next_move[1]
                    alpha = next_move[1]

                if (alpha is not None) & (beta is not None):
                    if alpha >= beta:
                        return max_index
            column += 1

        return max_index

    def minimize_play(self, game_board, depth, alpha, beta):
        score = game_board.score()
        if game_board.is_finished(depth, score):
            return [None, score]

        # Column, score
        min_index = [None, 99999]

        column = 0
        while column < self.columns:
            new_board = game_board.copy()
            if new_board.place(column):
                self.iterations += 1

                next_move = self.maximize_play(new_board, (depth - 1), alpha, beta)
                if (min_index[0] is None) | (next_move[1] < min_index[1]):
                    min_index[0] = column
                    min_index[1] = next_move[1]
                    beta = next_move[1]

                if (alpha is not None) & (beta is not None):
                    if alpha >= beta:
                        return min_index
            column += 1

        return min_index

    def switch_round(self, round_switch):
        # 0 Human, 1 Computer
        if round_switch == 0:
            return 1
        else:
            return 0

    def update_status(self):
        if self.board.score() == -self.score:
            self.status = 1
            print("Human won")
            # Human won
        if self.board.score() == self.score:
            self.status = 2
            print("Com won")
            # Computer won
        if self.board.is_full() is True:
            self.status = 3
            print("Tie!")
            # Tie
