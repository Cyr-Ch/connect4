import game
# Main Program


def print_board(board_field):
    i = 0
    j = 0
    while i < 6:
        print(repr(i + 1) + ": ", end='', flush=True)
        while j < 7:
            if board_field[i][j] is None:
                print(" ", end='', flush=True)
            else:
                if board_field[i][j] == 0:
                    print("o", end='', flush=True)
                else:
                    print("x", end='', flush=True)
            j += 1
        print("")
        i += 1
        j = 0
    print("   1234567")

game = game.Game()
print_board(game.board.field)
while True:
    input_var = int(input('Next Move: '))
    input_var -= 1
    game.place(input_var)
    game.generate_computer_decision()
    print_board(game.board.field)
    if game.status != 0:
        break
    print(game.iterations)
print("Done.")
