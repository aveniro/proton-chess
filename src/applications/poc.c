/**
 * @file poc.c
 * @author Nathan Seymour
 * @brief A simple application showing the creation and saving of a chess board.
 */

#include <stdio.h>
#include "chess.h"

int main()
{
    printf("Creating new chess board...\n");
    chess_board *board = cb_new_chess_board();

    printf("Initializing chess board...\n");
    cb_initialize_game(board);

    char buffer[CB_FEN_NOTATION_LENGTH];
    cb_generate_fen(board, buffer, CB_FEN_NOTATION_LENGTH);

    printf("FEN Notation of current game: %s\n", (char*) buffer);

    printf("Saving game to chess_game.pcgf...\n");
    cb_write_board_to_file(board, "chess_game.pcgf");

    printf("Freeing chess board...\n");
    cb_free_chess_board(board);
    return 0;
}
