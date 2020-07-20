# Creates an instance of Board.
#
# @constructor
# @this {Board}
# @param {Game} game The main-game object.
# @param {array} field The field containing our situation.
# @param {number} player The current player.

import copy


class Board:

    def __init__(self, game, field, player):
        self.game = game
        self.field = field
        self.player = player

    # Determines if situation is finished.
    #
    # @param {number} depth
    # @param {number} score
    # @return {boolean}

    def is_finished(self, depth, score):
        if (depth == 0) | (score == self.game.score) | (score == -self.game.score) | (self.is_full is True):
            return True
        return False

    # Place in current board.
    #
    # @param {number} column
    # @return {boolean}
    def place(self, column):
        # Check if column valid
        # 1. not empty 2. not exceeding the board size
        if (self.field[0][column] is None) & (column >= 0) & (column < self.game.columns):
            i = (self.game.rows - 1)
            # Bottom to top
            while i >= 0:
                if self.field[i][column] is None:
                    # Set current player coin
                    self.field[i][column] = self.player
                    break
                    # Break from loop after inserting
                i -= 1

            self.player = self.game.switch_round(self.player)
            return True
        else:
            return False

    # Return a score for various positions (either horizontal, vertical or diagonal by moving through our board).
    #
    # @param {number} row
    # @param {number} column
    # @param {number} delta_y
    # @param {number} delta_x
    # @return {number}

    def score_position(self, row, column, delta_y, delta_x):
        human_points = 0
        computer_points = 0

        # Save winning positions to arrays for later usage
        self.game.winning_array_human = []
        self.game.winning_array_cpu = []

        # Determine score through amount of available chips
        i = 0
        while i < 4:
            if self.field[row][column] == 0:
                self.game.winning_array_human.append([row, column])
                human_points += 1
                # Add for each human chip
            elif self.field[row][column] == 1:
                self.game.winning_array_cpu.append([row, column])
                computer_points += 1
                # Add for each computer chip
            # Moving through our board
            row += delta_y
            column += delta_x
            i += 1

        # Marking winning/returning score
        if human_points == 4:
            self.game.winning_array = self.game.winning_array_human
            # Computer won (100000)
            return -self.game.score
        elif computer_points == 4:
            self.game.winning_array = self.game.winning_array_cpu
            # Human won (-100000)
            return self.game.score
        else:
            # Return normal points
            return computer_points

    # Returns the overall score for our board.
    #
    # @return {number}

    def score(self):

        vertical_points = 0
        horizontal_points = 0
        diagonal_points1 = 0
        diagonal_points2 = 0

        # Board-size: 7x6 (height x width)
        # Array indices begin with 0
        # => e.g. height: 0, 1, 2, 3, 4, 5

        # Vertical points
        # Check each column for vertical score
        #
        # Possible situations
        #  0  1  2  3  4  5  6
        # [x][ ][ ][ ][ ][ ][ ] 0
        # [x][x][ ][ ][ ][ ][ ] 1
        # [x][x][x][ ][ ][ ][ ] 2
        # [x][x][x][ ][ ][ ][ ] 3
        # [ ][x][x][ ][ ][ ][ ] 4
        # [ ][ ][x][ ][ ][ ][ ] 5

        row = 0
        while row < self.game.rows - 3:
            # Für jede Column überprüfen
            column = 0
            while column < self.game.columns:
                # Die Column bewerten und zu den Punkten hinzufügen
                score = self.score_position(row, column, 1, 0)
                if score == self.game.score:
                    return self.game.score
                if score == -self.game.score:
                    return -self.game.score
                vertical_points += score
                column += 1
            row += 1

        # Horizontal points
        # Check each row's score
        #
        # Possible situations
        #  0  1  2  3  4  5  6
        # [x][x][x][x][ ][ ][ ] 0
        # [ ][x][x][x][x][ ][ ] 1
        # [ ][ ][x][x][x][x][ ] 2
        # [ ][ ][ ][x][x][x][x] 3
        # [ ][ ][ ][ ][ ][ ][ ] 4
        # [ ][ ][ ][ ][ ][ ][ ] 5

        row = 0
        while row < self.game.rows:
            column = 0
            while column < self.game.columns - 3:
                score = self.score_position(row, column, 0, 1)
                if score == self.game.score:
                    return self.game.score
                if score == -self.game.score:
                    return -self.game.score
                horizontal_points += score
                column += 1
            row += 1

        # Diagonal points 1 (left-bottom)
        #
        # Possible situation
        #  0  1  2  3  4  5  6
        # [x][ ][ ][ ][ ][ ][ ] 0
        # [ ][x][ ][ ][ ][ ][ ] 1
        # [ ][ ][x][ ][ ][ ][ ] 2
        # [ ][ ][ ][x][ ][ ][ ] 3
        # [ ][ ][ ][ ][ ][ ][ ] 4
        # [ ][ ][ ][ ][ ][ ][ ] 5

        row = 0
        while row < self.game.rows - 3:
            column = 0
            while column < self.game.columns - 3:
                score = self.score_position(row, column, 1, 1)
                if score == self.game.score:
                    return self.game.score
                if score == -self.game.score:
                    return -self.game.score
                diagonal_points1 += score
                column += 1
            row += 1

        # Diagonal points 2 (right-bottom)
        #
        # Possible situation
        #  0  1  2  3  4  5  6
        # [ ][ ][ ][x][ ][ ][ ] 0
        # [ ][ ][x][ ][ ][ ][ ] 1
        # [ ][x][ ][ ][ ][ ][ ] 2
        # [x][ ][ ][ ][ ][ ][ ] 3
        # [ ][ ][ ][ ][ ][ ][ ] 4
        # [ ][ ][ ][ ][ ][ ][ ] 5

        row = 3
        while row < self.game.rows:
            column = 0
            while column < self.game.columns - 3:
                score = self.score_position(row, column, -1, +1)
                if score == self.game.score:
                    return self.game.score
                if score == -self.game.score:
                    return -self.game.score
                diagonal_points2 += score
                column += 1
            row += 1

        points = horizontal_points + vertical_points + diagonal_points1 + diagonal_points2
        return points

    # Determines if board is full.
    #
    # @return {boolean}

    def is_full(self):
        i = 0
        while i < self.game.columns:
            if self.field[0][i] is None:
                return False
            i += 1
        return True

    # Returns a copy of our board.
    #
    # @return {Board}

    def copy(self):
        new_board = copy.deepcopy(self)
        return new_board
